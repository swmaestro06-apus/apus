%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyerror(char const *str);

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
    | type_specifier ID ASSIGN const_expression
    | struct_union_type ID ID ASSIGN const_expression_list
    | type_specifier array
    | struct_union_type ID array
    ;
const_expression_list :
    const_expression
    | const_expression comma_line_opt const_expression_list
    ;
const_expression :
    expression
    | struct_init
    | array_init
    ;
struct_init :
    block_start const_expression_list block_end
    ;
array_init : 
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
    /* empty */
    | expression
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
    ASSIGN | ADDASSIGN | SUBASSIGN
    | MULASSIGN | DIVASSIGN | MODASSIGN
    | ORASSIGN | ANDASSIGN | XORASSIGN
    | LSASSIGN | RSASSIGN
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
    block_start action_declaration_opt block_end
    ;
if_statement :
    IF paren_start expression paren_end block_statement else_if
    ;
else_if :
    /* empty */
    | ELSE if_statement
    | ELSE block_statement
    ;
for_statement :
    FOR paren_start expression_opt semi_start expression_opt semi_start expression_opt paren_end block_statement
    ;
jump_statement :
    BREAK line_list
    | CONTINUE line_list
    | RETURN expression_opt line_list
    | EXIT expression_opt line_list
    ;
expression_statement :
    expression line_list
    ;
var_def_statement :
    VAR member_definition line_list
    ;
%%
int yyerror(char const *str) {
    extern char yylineno;
    extern char *yytext;
    fprintf(stderr, "parser error near %s, line is %d\n", yytext, yylineno);
    return 0;
}
