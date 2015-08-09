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
%token<str_val> STRING_LITERAL
%token<str_val> ID

%token<int_val> U8 U16 U32 U64
%token<int_val> S8 S16 S32 S64
%token<double_val> F32 F64
%token<char_val> C8 C16 C32
%token<str_val> STR STR8 STR16 STR32
%token STRUCT CONST UNION

%token L_BRACE R_BRACE L_CASE R_CASE OPEN CLOSE
%token COMMENT CR DOT VAR SEMI
%token INCLUDE IF ELSE FOR EXIT TRUE FALSE RETURN

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

%%
program :
    data_declaration_opt action_declaration_opt
    ;
data_declaration_opt :
    /* empty */
    | data_declaration_list
    ;
action_declaration_opt :
    /* empty */
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
    action_declaration
    | action_declaration action_declaration_list
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
    | type_specifier ID ASSIGN expression
    | struct_union_type ID ID ASSIGN expression
    | type_specifier array
    | struct_union_type ID array
    ;
array :
    L_CASE expression R_CASE ID
    | L_CASE expression R_CASE ID ASSIGN expression
    ;
expression :
    expression assign_operator expression
    | expression LOR expression
    | expression LAND expression
    | expression OR expression
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
    | CHAR_LITERAL
    | STRING_LITERAL
    | var_expression
    ;
var_expression :
    ID
    ;
block_start :
    line_opt L_BRACE line_opt
    ;
type_specifier :
    U8 | U16 | U32 | U64
    | S8 | S16 | S32 | S64
    | F32 | F64
    | C8 | C16 | C32
    | STR | STR8 | STR16 | STR32
    ;
assign_operator :
    ASSIGN | ADDASSIGN | SUBASSIGN
    | MULASSIGN | DIVASSIGN | MODASSIGN
    | ORASSIGN | ANDASSIGN | XORASSIGN
    | LSASSIGN | RSASSIGN
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
