%{
#include <stdio.h>
#include <stdlib.h>

#include "parser_context.h"

extern int yylex();
extern int yyerror(apus::ParserContext* pctx, char const *str);

%}

%parse-param {
    apus::ParserContext* pctx
}

%code requires {
    #include <memory>
    #include <list>
    #include <string>

    #include "common/common.h"
    #include "ast/statement/statement.h"
    #include "ast/statement/block.h"
    #include "ast/statement/for_statement.h"
    #include "ast/statement/if_statement.h"
    #include "ast/statement/jump_statement.h"
    #include "ast/statement/expression_statement.h"
    #include "ast/statement/var_def_statement.h"

    #include "vm/virtual_machine.h"

    #include "ast/expression.h"

    #include "ast/value/value.h"

    using namespace std;
    using namespace apus;

}

%union {
    int64_t int_val;
    double double_val;
    int char_val;
    char* str_val;

    TypeSpecifier type_spec;
    DataType* data_type;

    list<shared_ptr<Expression>>* list_expr;
    list<shared_ptr<Statement>>* list_stmt;

    Statement* stmt;

    Expression* expr;
    Expression::Type expr_type;

    Value* value;
}

%token<int_val> INT_LITERAL
%token<double_val> DOUBLE_LITERAL
%token<char_val> CHAR_LITERAL
%token<str_val> STRING_LITERAL
%token<str_val> ID
%token<int_val> BINARY_LITERAL OCTA_LITERAL HEXA_LITERAL

%token<type_spec> UINT8 UINT16 UINT32 UINT64
%token<type_spec> SINT8 SINT16 SINT32 SINT64
%token<type_spec> FLOAT32 FLOAT64
%token<type_spec> CHAR8 CHAR16 CHAR32
%token<type_spec> STRING8 STRING16 STRING32
%token<type_spec> STRUCT CONST UNION

%token L_BRACE R_BRACE L_CASE R_CASE OPEN CLOSE
%token COMMENT CR DOT VAR SEMI COMMA
%token INCLUDE IF ELSE FOR EXIT TRUE FALSE CONTINUE BREAK RETURN

%right ASSIGN ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ORASSIGN ANDASSIGN XORASSIGN LSASSIGN RSASSIGN
%left LOR
%left LAND
%left OR
%left XOR
%left AND
%left EQL NEQ
%left LSS GTR LEQ GEQ
%left LSHIFT RSHIFT
%left ADD SUB
%left MUL DIV MOD
%right NOT REVERSE

%type<list_stmt> action_declaration_list action_declaration_opt
%type<list_expr> const_expression_list

%type<stmt> action_declaration for_statement if_statement else_if jump_statement expression_statement var_def_statement block_statement

%type<expr> expression expression_opt unary_expression primary_expression variable_expression init_expression const_expression

%type<type_spec> type_specifier struct_union_type

%type<data_type> dimension_array

%%
program :
    data_declaration_opt action_declaration_opt {
        pctx->getVM()->setStmtList(*$2);
    }
    ;
data_declaration_opt :
    /* empty */
    | data_declaration_list
    ;
action_declaration_opt :
    /* empty */ { $$ = new list<shared_ptr<Statement>>(); }
    | action_declaration_list
    ;
line_opt :
    /* empty */
    | line_list
    ;
line_list :
    CR
    | CR line_list
    ;
data_declaration_list :
    data_declaration
    | data_declaration_list data_declaration
    | line_list data_declaration_list
    ;
action_declaration_list :
    action_declaration {
        $$ = new list<shared_ptr<Statement>>();
        $$->push_back(shared_ptr<Statement>($1));
    }
    | action_declaration action_declaration_list {
        $2->push_front(shared_ptr<Statement>($1));
        $$ = $2;
    }
    ;
data_declaration :
    struct_union_type ID {
        pctx->setCurrentDataType(std::make_shared<DataType>($1));
        pctx->setCurrentName(new string($2));
        
    } block_start member_definition_list R_BRACE line_list {
        pctx->ChangeCurrentDataType();
    } 
    ;
struct_union_type :
    STRUCT { $$ = TypeSpecifier::STRUCT; }
    | UNION { $$ = TypeSpecifier::UNION; }
    ;
member_definition_list :
    member_definition line_opt
    | member_definition line_list member_definition_list
    ;
member_definition :
    type_specifier ID {
        pctx->AddToCurrentDataType(new string($2), $1);
    }
    | struct_union_type ID ID {
        pctx->AddToCurrentDataType(new string($3), new string($2));
    }
    | type_specifier ID ASSIGN const_expression {
        std::shared_ptr<DataType> dt = std::make_shared<DataType>($1);
        dt->SetInitExpr($4);
        pctx->AddToCurrentDataType(new string($2), dt);
    }
    | struct_union_type ID ID ASSIGN const_expression {
        std::shared_ptr<DataType> dt 
            = pctx->getDataTypeTable()->Find(new string($2))->Copy();
        dt->SetInitExpr($5);
        pctx->AddToCurrentDataType(new string($3), dt);
    }
    | type_specifier dimension_array ID {
        $2->setElement(pctx->getDataTypeTable()->Find($1));
        pctx->AddToCurrentDataType(new string($3), $2);
    }
    | type_specifier dimension_array ID ASSIGN const_expression_list {
        $2->setElement(pctx->getDataTypeTable()->Find($1));
        $2->SetInitExpr($5);
        pctx->AddToCurrentDataType(new string($3), $2);
    }
    | struct_union_type ID dimension_array ID {
        $3->setElement(pctx->getDataTypeTable()->Find(new string($2));
        pctx->AddToCurrentDataType(new string($4), $3);
    }
    | struct_union_type ID dimension_array ID ASSIGN const_expression_list {
        $3->setElement(pctx->getDataTypeTable()->Find(new string($2));
        $3->SetInitExpr($6);
        pctx->AddToCurrentDataType(new string($4), $3);
    }
    ;
const_expression_list :
    const_expression
    | const_expression comma_line_opt const_expression_list
    ;
const_expression :
    INT_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::S64, $1)); }
    | DOUBLE_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::F64, $1)); }
    | CHAR_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::C8, $1)); }
    | STRING_LITERAL
    | const_struct_init
    | const_array_init
    ;
const_struct_init :
    block_start const_expression_list block_end
    ;
const_array_init : 
    L_CASE const_expression_list R_CASE
    ;
dimension_array :
    L_CASE expression R_CASE {
        DataType* dt = new ArrayDataType();
        ArrayDataType* adt = std::dynamic_cast<ArrayDataType*>(dt);
        dt->AddDimension($2);
        $$ = dt;
    }
    | L_CASE expression R_CASE dimension_array {
        DataType* dt = $4;
        ArrayDataType* adt = std::dynamic_cast<ArrayDataType*>(dt);
        adt->AddDimension($2);
        $$ = dt;
    }
    ;
expression_opt :
    /* empty */
    | expression
    ;
expression :
    variable_expression ASSIGN expression
    | variable_expression ADDASSIGN expression
    | variable_expression SUBASSIGN expression
    | variable_expression MULASSIGN expression
    | variable_expression DIVASSIGN expression
    | variable_expression MODASSIGN expression
    | variable_expression ORASSIGN expression
    | variable_expression XORASSIGN expression
    | variable_expression ANDASSIGN expression
    | variable_expression LSASSIGN expression
    | variable_expression RSASSIGN expression
    | expression LOR expression { $$ = new BinaryExpression(Expression::EXP_LOR, $1, $3); }
    | expression LAND expression { $$ = new BinaryExpression(Expression::EXP_LAND, $1, $3); }
    | expression OR expression { $$ = new BinaryExpression(Expression::EXP_OR, $1, $3); }
    | expression XOR expression { $$ = new BinaryExpression(Expression::EXP_XOR, $1, $3); }
    | expression AND expression { $$ = new BinaryExpression(Expression::EXP_AND, $1, $3); }
    | expression EQL expression { $$ = new BinaryExpression(Expression::EXP_EQL, $1, $3); }
    | expression NEQ expression { $$ = new BinaryExpression(Expression::EXP_NEQ, $1, $3); }
    | expression LSS expression { $$ = new BinaryExpression(Expression::EXP_LSS, $1, $3); }
    | expression GTR expression { $$ = new BinaryExpression(Expression::EXP_GTR, $1, $3); }
    | expression LEQ expression { $$ = new BinaryExpression(Expression::EXP_LEQ, $1, $3); }
    | expression GEQ expression { $$ = new BinaryExpression(Expression::EXP_GEQ, $1, $3); }
    | expression LSHIFT expression { $$ = new BinaryExpression(Expression::EXP_LSHIFT, $1, $3); }
    | expression RSHIFT expression { $$ = new BinaryExpression(Expression::EXP_RSHIFT, $1, $3); }
    | expression ADD expression { $$ = new BinaryExpression(Expression::EXP_ADD, $1, $3); }
    | expression SUB expression { $$ = new BinaryExpression(Expression::EXP_SUB, $1, $3); }
    | expression MUL expression { $$ = new BinaryExpression(Expression::EXP_MUL, $1, $3); }
    | expression DIV expression { $$ = new BinaryExpression(Expression::EXP_DIV, $1, $3); }
    | expression MOD expression { $$ = new BinaryExpression(Expression::EXP_MOD, $1, $3); }
    | unary_expression
    ;
unary_expression :
    primary_expression
    | NOT unary_expression { $$ = new UnaryExpression(Expression::EXP_NOT, $2); }
    | REVERSE unary_expression { $$ = new UnaryExpression(Expression::EXP_REVERSE, $2); }
    | SUB primary_expression { $$ = new UnaryExpression(Expression::EXP_SUB, $2); }
    | ADD primary_expression { $$ = new UnaryExpression(Expression::EXP_ADD, $2); }
    ;
primary_expression :
    OPEN expression CLOSE { $$ = $2; }
    | INT_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::S64, $1)); }
    | DOUBLE_LITERAL { $$ = new ValueExpression(FloatIntValue::Create(TypeSpecifier::F64, $1)); }
    | CHAR_LITERAL { $$ = new ValueExpression(CharacterValue::Create(TypeSpecifier::C8, $1)); }
    | STRING_LITERAL
    | BINARY_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::S64, $1)); }
    | OCTA_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::S64, $1)); }
    | HEXA_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(TypeSpecifier::S64, $1)); }
    | variable_expression
    | function_expression
    ;
variable_expression :
    ID
    | ID dimension_array
    | variable_expression DOT variable_expression
    ;
function_expression :
    ID OPEN arg_expression_opt CLOSE
    ;
arg_expression_opt :
    /* empty */
    | arg_expression_list
    ;
arg_expression_list :
    expression
    | expression comma_line_opt arg_expression_list
    ;
comma_line_opt :
    COMMA line_opt
    ;
block_start :
    line_opt L_BRACE line_opt
    ;
block_end :
    R_BRACE line_opt
    ;
paren_start :
    line_opt OPEN line_opt
    ;
paren_end :
    line_opt CLOSE
    ;
semi_start :
    line_opt SEMI line_opt
    ;
type_specifier :
    UINT8 { $$ = TypeSpecifier::U8; }
    | UINT16 { $$ = TypeSpecifier::U16; }
    | UINT32 { $$ = TypeSpecifier::U32; }
    | UINT64 { $$ = TypeSpecifier::U64; }
    | SINT8 { $$ = TypeSpecifier::S8; }
    | SINT16 { $$ = TypeSpecifier::S16; }
    | SINT32 { $$ = TypeSpecifier::S32; }
    | SINT64 { $$ = TypeSpecifier::S64; }
    | FLOAT32 { $$ = TypeSpecifier::F32; }
    | FLOAT64 { $$ = TypeSpecifier::F64; }
    | CHAR8 { $$ = TypeSpecifier::C8; }
    | CHAR16 { $$ = TypeSpecifier::C16; }
    | CHAR32 { $$ = TypeSpecifier::C32; }
    | STRING8 { $$ = TypeSpecifier::STR8; }
    | STRING16 { $$ = TypeSpecifier::STR16; }
    | STRING32 { $$ = TypeSpecifier::STR32; }
    ;
action_declaration : 
    block_statement
    | if_statement
    | for_statement
    | jump_statement
    | expression_statement
    | var_def_statement
    ;
block_statement :
    block_start action_declaration_opt block_end { $$ = new Block(*$2); }
    ;
if_statement :
    IF paren_start expression paren_end block_statement else_if { $$ = new IfStatement($3, $5, $6); }
    ;
else_if :
    /* empty */ { $$ = nullptr; }
    | ELSE if_statement { $$ = $2; }
    | ELSE block_statement { $$ = $2; }
    ;
for_statement :
    FOR paren_start expression_opt semi_start expression_opt semi_start expression_opt paren_end block_statement { $$ = new ForStatement($3, $5, $7, $9); }
    ;
jump_statement :
    BREAK line_list { $$ = new BreakStatement(); }
    | CONTINUE line_list { $$ = new ContinueStatement(); }
    | RETURN expression_opt line_list { $$ = new ReturnStatement($2); }
    | EXIT expression_opt line_list { $$ = new ExitStatement($2); }
    ;
expression_statement :
    expression line_list { $$ = new ExpressionStatement($1); }
    ;
var_def_statement :
    VAR variable_definition line_list { $$ = new VarDefStatement(); }
    ;
variable_definition :
    type_specifier ID
    | struct_union_type ID ID
    | type_specifier ID ASSIGN init_expression
    | struct_union_type ID ID ASSIGN init_expression
    | type_specifier dimension_array ID
    | type_specifier dimension_array ID ASSIGN init_expression
    | struct_union_type ID dimension_array ID
    | struct_union_type ID dimension_array ID ASSIGN init_expression
    ;
init_expression_list :
    init_expression
    | init_expression comma_line_opt init_expression_list
    ;
init_expression :
    expression
    | struct_init
    | array_init
    ;
struct_init :
    block_start init_expression_list block_end
    ;
array_init : 
    L_CASE init_expression_list R_CASE
    ;
%%
int yyerror(apus::ParserContext* pctx, char const *str) {
    extern char yylineno;
    extern char *yytext;
    fprintf(stderr, "parser error near %s, line is %d\n", yytext, yylineno);
    return 0;
}
