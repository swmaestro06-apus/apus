%{
#include <stdio.h>
#include <stdlib.h>
%}
%union {
    int64_t int_val;
    double double_val;
    int char_val;
    char* str_val;
}
%token<int_val> INT_LITERAL
%token<double_val> DOUBLE_LITERAL
%token<char_val> CHAR_LITERAL
%token<str_val> ID

%token<int_val> U8 U16 U32 U64
%token<int_val> S8 S16 S32 S64
%token<double_cal> F32 F64
%token<char_val> C8 C16 C32
%token<str_val> STR STR8 STR16 STR32
%token STRUCT CONST UNION

%token L_BRACE R_BRACE L_CASE R_CASE OPEN CLOSE
%token COMMENT CR QUO DOT VAR SEMI
%token INCLUDE IF ELSE FOR EXIT TRUE FALSE RETURN

%right ASSIGN
%left OR
%left XOR
%left AND
%left EQL NEQ
%left LSS GTR LEQ GEQ
%left LSHIFT RSHIFT
%left ADD SUB
%left MUL DIV MOD
%right NOT REVERSE

%type<int_val> type_declaration local_type_declaration
%type<int_val> expression unary_expression primary_expression
%%
program :
    declaration_list
    ;
declaration_list : 
    declaration
    | declaration declaration_list
    ;
declaration : 
    data_declaration
    | action_declaration
    ;
data_declaration :
    VAR union_declaration
    | VAR struct_declaration
    | VAR type_declaration
    | CR
    ;
type_declaration :
    type_specifier ID
    | type_specifier ID ASSIGN expression
    | type_specifier array
    ;
array :
    L_CASE expression R_CASE ID
    | L_CASE expression R_CASE ID ASSIGN expression
    ;
expression :
    expression OR expression
    | expression XOR expression
    | expression AND expression
    | expression EQL expression
    | expression NEQ expression
    | expression LSS expression
    | expression GTR expression
    | expression LEQ expression
    | expression GEQ expression
    | expression LSHIFT expression
    | expression RSHIFT expression
    | expression ADD expression
    | expression SUB expression
    | expression MUL expression
    | expression DIV expression
    | expression MOD expression
    | unary_expression
    ;
unary_expression :
    primary_expression
    | NOT unary_expression
    | REVERSE unary_expression
    | SUB primary_expression
    | ADD primary_expression
    ;
primary_expression :
    OPEN expression CLOSE
    | INT_LITERAL
    | DOUBLE_LITERAL
    ;
union_declaration :
    UNION ID L_BRACE local_declaration_list R_BRACE
    | UNION ID CR L_BRACE local_declaration_list R_BRACE
    ;
struct_declaration :
    STRUCT ID L_BRACE local_declaration_list R_BRACE
    | STRUCT ID CR L_BRACE local_declaration_list R_BRACE
    ;
local_declaration_list :
    local_declaration
    | local_declaration local_declaration_list
    ;
local_declaration :
    type_declaration
    | CR
    ;
type_specifier :
    U8 | U16 | U32 | U64
    | S8 | S16 | S32 | S64
    | F32 | F64
    | C8 | C16 | C32
    | STR | STR8 | STR16 | STR32
    ;
action_declaration : 
    DOUBLE_LITERAL
    ;
%%
int yyerror(char const *str) {
    extern char yylineno;
    extern char *yytext;
    fprintf(stderr, "parser error near %s, line is %d\n", yytext, yylineno);
    return 0;
}
