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
    #include <iostream>

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
    #include "ast/value/signed_int_value.h"
    #include "ast/value/unsigned_int_value.h"
    #include "ast/value/float_value.h"
    #include "ast/value/character_value.h"
    #include "ast/value/string_value.h"

    using namespace std;
    using namespace apus;

    typedef shared_ptr<Statement> StmtPtr;
    typedef list<StmtPtr> ListStmt;
    typedef shared_ptr<ListStmt> ListStmtPtr; 
}

%union {
    int64_t int_val;
    uint64_t uint_val;
    double double_val;
    int char_val;
    char* str_val;

    TypeSpecifier type_specifier;

    list<shared_ptr<Statement>>* list_stmt;
    list<shared_ptr<Expression>>* list_expr;

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
%token<uint_val> BINARY_LITERAL OCTA_LITERAL HEXA_LITERAL

%token<type_spec> UINT8 UINT16 UINT32 UINT64
%token<type_spec> SINT8 SINT16 SINT32 SINT64
%token<type_spec> FLOAT32 FLOAT64
%token<type_spec> CHAR8 CHAR16 CHAR32
%token<type_spec> STRING STRING8 STRING16 STRING32
%token<type_spec> STRUCT_TYPE CONST_TYPE UNION_TYPE

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
%type<list_expr> arg_expression_list arg_expression_opt
%type<stmt> action_declaration for_statement if_statement else_if jump_statement expression_statement var_def_statement variable_definition block_statement

%type<expr> expression expression_opt unary_expression primary_expression variable_expression init_expression const_expression function_expression
%type<expr_type> assign_operator
%type<type_specifier> type_specifier struct_union_type

%%
program :
    line_opt data_declaration_opt action_declaration_opt {
        pctx->SendDataTypeTableToVM();
        pctx->getVM()->setStmtList(*$3);
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
        pctx->setCurrentName(string($2));
    } block_start member_definition_list R_BRACE line_list {
        pctx->ChangeCurrentDataType();
    }
    ;
struct_union_type :
    STRUCT_TYPE { $$ = TypeSpecifier::STRUCT; }
    | UNION_TYPE { $$ = TypeSpecifier::UNION; }
    ;
member_definition_list :
    member_definition line_opt
    | member_definition line_list member_definition_list
    ;
member_definition :
    type_specifier ID {
        pctx->AddToCurrentDataType(string($2), $1);
    }
    | struct_union_type ID ID {
        pctx->AddToCurrentDataType(string($3), string($2));
    }
    | type_specifier ID ASSIGN const_expression
    | struct_union_type ID ID ASSIGN const_expression
    | type_specifier dimension_array ID
    | type_specifier dimension_array ID ASSIGN const_expression_list
    | struct_union_type ID dimension_array ID
    | struct_union_type ID dimension_array ID ASSIGN const_expression_list
    ;
const_expression_list :
    const_expression
    | const_expression comma_line_opt const_expression_list
    ;
const_expression :
    INT_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(pctx->getDataTypeTable()->Find(S64), $1)); }
    | DOUBLE_LITERAL { $$ = new ValueExpression(FloatValue::Create(pctx->getDataTypeTable()->Find(F64), $1)); }
    | CHAR_LITERAL { $$ = new ValueExpression(CharacterValue::Create(pctx->getDataTypeTable()->Find(C8), $1)); }
    | STRING_LITERAL { $$ = new ValueExpression(StringValue::Create(pctx->getDataTypeTable()->Find(STR8), $1)); }
    | BINARY_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
    | OCTA_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
    | HEXA_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
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
    L_CASE expression R_CASE
    | L_CASE expression R_CASE dimension_array
    ;
expression_opt :
    /* empty */ { $$ = nullptr; }
    | expression
    ;
expression :
    variable_expression assign_operator expression { $$ = new AssignExpression($2, $1, $3);}
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
    | INT_LITERAL { $$ = new ValueExpression(SignedIntValue::Create(pctx->getDataTypeTable()->Find(S64), $1)); }
    | DOUBLE_LITERAL { $$ = new ValueExpression(FloatValue::Create(pctx->getDataTypeTable()->Find(F64), $1)); }
    | CHAR_LITERAL { $$ = new ValueExpression(CharacterValue::Create(pctx->getDataTypeTable()->Find(C8), $1)); }
    | STRING_LITERAL { $$ = new ValueExpression(StringValue::Create(pctx->getDataTypeTable()->Find(STR8), $1)); }
    | BINARY_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
    | OCTA_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
    | HEXA_LITERAL { $$ = new ValueExpression(UnsignedIntValue::Create(pctx->getDataTypeTable()->Find(U64), $1)); }
    | variable_expression
    | function_expression
    ;
variable_expression :
    ID { $$ = new VariableExpression(std::string($1)); }
    | ID dimension_array
    | variable_expression DOT ID
    | variable_expression DOT ID dimension_array
    ;
function_expression :
    ID OPEN arg_expression_opt CLOSE { $$ = new FunctionExpression(string($1), *$3); }
    ;
arg_expression_opt :
    /* empty */ { $$ = new list<shared_ptr<Expression>>(); }
    | arg_expression_list
    ;
arg_expression_list :
    expression {
        $$ = new list<shared_ptr<Expression>>();
        $$->push_back(shared_ptr<Expression>($1));
    }
    | expression comma_line_opt arg_expression_list {
        $3->push_front(shared_ptr<Expression>($1));
        $$ = $3;
    }
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
    | STRING { $$ = TypeSpecifier::STR8; }
    | STRING8 { $$ = TypeSpecifier::STR8; }
    | STRING16 { $$ = TypeSpecifier::STR16; }
    | STRING32 { $$ = TypeSpecifier::STR32; }
    ;
assign_operator :
    ASSIGN { $$ = Expression::EXP_ASSIGN; }
    | ADDASSIGN { $$ = Expression::EXP_ADDASSIGN; }
    | SUBASSIGN { $$ = Expression::EXP_SUBASSIGN; }
    | MULASSIGN { $$ = Expression::EXP_MULASSIGN; }
    | DIVASSIGN { $$ = Expression::EXP_DIVASSIGN; }
    | MODASSIGN { $$ = Expression::EXP_MODASSIGN; }
    | ORASSIGN { $$ = Expression::EXP_ORASSIGN; }
    | ANDASSIGN { $$ = Expression::EXP_ANDASSIGN; }
    | XORASSIGN {  $$ = Expression::EXP_XORASSIGN; }
    | LSASSIGN { $$ = Expression::EXP_LSASSIGN; }
    | RSASSIGN { $$ = Expression::EXP_RSASSIGN; }
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
    VAR variable_definition line_list { $$ = $2;}
    ;
variable_definition :
    type_specifier ID
    | struct_union_type ID ID
    | type_specifier ID ASSIGN init_expression { $$ = new VarDefStatement($1, $2, $4); }
    | struct_union_type ID ID ASSIGN init_expression
    | type_specifier dimension_array ID
    | type_specifier dimension_array ID ASSIGN init_expression_list
    | struct_union_type ID dimension_array ID
    | struct_union_type ID dimension_array ID ASSIGN init_expression_list
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
