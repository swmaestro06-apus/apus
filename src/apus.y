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

    #include <iostream>

    #include <memory>
    #include <list>

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

    typedef shared_ptr<Statement> StmtPtr;
    typedef list<StmtPtr> ListStmt;
    typedef shared_ptr<ListStmt> ListStmtPtr; 
}

%union {
    int64_t int_val;
    double double_val;
    int char_val;
    char* str_val;

    list<shared_ptr<Statement>>* list_stmt;

    Statement* stmt;
    Block* block_stmt;

    Expression* expr;
    Expression::Type expr_type;

    Value* value;
}

%token<int_val> INT_LITERAL
%token<double_val> DOUBLE_LITERAL
%token<char_val> CHAR_LITERAL
%token<str_val> STRING_LITERAL
%token<str_val> ID

%token<int_val> U8 U16 U32 U64
%token<int_val> S8 S16 S32 S64
%token<double_val> F32 F64
%token<char_val> C8 C16 C32
%token<str_val> STR STR8 STR16 STR32
%token STRUCT CONST UNION

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
%type<stmt> action_declaration for_statement if_statement else_if jump_statement expression_statement var_def_statement
%type<block_stmt> block_statement

%type<expr> expression expression_opt unary_expression primary_expression 
%type<expr_type> assign_operator

%%
program :
    data_declaration_opt action_declaration_opt { 
        pctx->getVM()->setStmtList(*$2);
        cout << "Program : action_decl_list size "<< $2->size()  << endl;
    }
    ;
data_declaration_opt :
    /* empty */
    | data_declaration_list
    ;
action_declaration_opt :
    /* empty */ {$$ = nullptr; }
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
    | data_declaration data_declaration_list
    | line_list data_declaration_list
    ;
action_declaration_list :
    action_declaration {
        // access VM Directly
        // E.G. pctx->getVM()->getStmtList()->push_back($1);
        //ListStmtPtr list_stmt_ptr = make_shared<ListStmt>();
        //list_stmt_ptr->push_back(*$1);

        cout << "Action Decl List CREATED" << endl;

        $$ = new list<shared_ptr<Statement>>();
        $$->push_back(shared_ptr<Statement>($1));
    }
    | action_declaration action_declaration_list {
        //$2->push_back($1);
        //$$ = $2;

        cout << "Action Decl PUSH_FRONT" << endl;
        
        $2->push_front(shared_ptr<Statement>($1));
        $$ = $2;
    }
    ;
data_declaration :
    struct_union_type ID block_start member_definition_list R_BRACE line_list
    ;
struct_union_type :
    STRUCT
    | UNION
    ;
member_definition_list :
    member_definition line_opt
    | member_definition line_list member_definition_list
    ;
member_definition :
    type_specifier ID
    | struct_union_type ID ID
    | type_specifier ID ASSIGN const_expression
    | struct_union_type ID ID ASSIGN const_expression
    | type_specifier array
    | struct_union_type ID array
    ;
const_expression_list :
    const_expression
    | const_expression comma_line_opt const_expression_list
    ;
const_expression :
    INT_LITERAL 
    | DOUBLE_LITERAL
    | CHAR_LITERAL
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
array :
    dimension_array ID
    | dimension_array ID ASSIGN const_expression_list
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
    expression assign_operator expression { /* $$ = new AssignExpression($2, $1, $3); */ }
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
    | INT_LITERAL
    | DOUBLE_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
    | variable_expression
    ;
variable_expression :
    ID
    | ID dimension_array
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
    U8 | U16 | U32 | U64
    | S8 | S16 | S32 | S64
    | F32 | F64
    | C8 | C16 | C32
    | STR | STR8 | STR16 | STR32
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
    block_start action_declaration_opt block_end { cout << "Block CREATED #statement is " << $2->size() <<endl; $$ = new Block(*$2); }
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
    | type_specifier array
    | struct_union_type ID array
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
