%{
#include <stdio.h>

#include "parser_context.h"
#include "y.tab.hh"

%}

%option noyywrap
%option yylineno

%%
"u8"    { return UINT8; }
"u16"   { return UINT16; }
"u32"   { return UINT32; }
"u64"   { return UINT64; }
"s8"    { return SINT8; }
"s16"   { return SINT16; }
"s32"   { return SINT32; }
"s64"   { return SINT64; }
"f32"   { return FLOAT32; }
"f64"   { return FLOAT64; }
"c8"    { return CHAR8; }
"c16"   { return CHAR16; }
"c32"   { return CHAR32; }
"str"   { return STRING; }
"str8"  { return STRING8; }
"str16" { return STRING16; }
"str32" { return STRING32; }
"var"   { return VAR; }

"include"  { return INCLUDE; }
"union"    { return UNION; }
"struct"   { return STRUCT; }
"const"    { return CONST; }
"if"       { return IF; }
"else"     { return ELSE; }
"for"      { return FOR; }
"continue" { return CONTINUE; }
"break"    { return BREAK; }
"return"   { return RETURN; }
"exit"     { return EXIT; }
"true"     { return TRUE; }
"false"    { return FALSE; }

"+="  { return ADDASSIGN; }
"-="  { return SUBASSIGN; }
"*="  { return MULASSIGN; }
"/="  { return DIVASSIGN; }
"%="  { return MODASSIGN; }
"|="  { return ORASSIGN; }
"&="  { return ANDASSIGN; }
"^="  { return XORASSIGN; }
"<<=" { return LSASSIGN; }
">>=" { return RSASSIGN; }
"<<"  { return LSHIFT; }
">>"  { return RSHIFT; }
"||"  { return LOR; }
"&&"  { return LAND; }
 
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"=" { return ASSIGN; }
"|" { return OR; }
"&" { return AND; }
"%" { return MOD; }
"~" { return REVERSE; }
"^" { return XOR; }

"==" { return EQL; }
"<"  { return LSS; }
">"  { return GTR; }
"<=" { return LEQ; }
">=" { return GEQ; }
"!=" { return NEQ; }
"!"  { return NOT; }
"."  { return DOT; }
";"  { return SEMI; }
","  { return COMMA; }

"{"  { return L_BRACE; }
"}"  { return R_BRACE; }
"["  { return L_CASE; }
"]"  { return R_CASE; }
"("  { return OPEN; }
")"  { return CLOSE; }
"\n" { return CR; }

([1-9][0-9]*|[0]) {
    int temp;
    sscanf(yytext, "%d", &temp);
    yylval.int_val = temp;
    return INT_LITERAL;
}
[0-9]*\.[0-9]* {
    double temp;
    sscanf(yytext, "%lf", &temp);
    yylval.double_val = temp;
    return DOUBLE_LITERAL;
}

[a-zA-Z_][0-9a-zA-Z_]* {
    yylval.str_val = (char*)malloc(yyleng);
    sprintf(yylval.str_val, "%s", yytext);
    // Sting control : yytext[NUM] 
    return ID;
}

'([^'\n|\\'])' {
    yylval.char_val = yytext[1];
    return CHAR_LITERAL;
}

\"([^"\n]|\\\")*\" {
    int i;
    yylval.str_val = (char*)malloc(yyleng-1);
    yytext[yyleng-1] = '\0';
    for(i = 0; i < yyleng-1; i++) {
        yylval.str_val[i] = yytext[i+1];
    }
    return STRING_LITERAL;
}

0b[0-1]* {
    int num_tmp;
    char* tmp = (char*)malloc(yyleng);
    sscanf(yytext, "0b%s", tmp);
    num_tmp = strtol(tmp, NULL, 2);
    yylval.int_val = num_tmp;
    free(tmp);
    return BINARY_LITERAL;
}

0[0-7]* {
    int num_tmp;
    char* tmp = (char*)malloc(yyleng);
    sscanf(yytext, "0%s", tmp);
    num_tmp = strtol(tmp, NULL, 8);
    yylval.int_val = num_tmp;
    free(tmp);
    return OCTA_LITERAL;
}

0x[0-9a-fA-F]* {
    int num_tmp;
    char* tmp = (char*)malloc(yyleng);
    sscanf(yytext, "0x%s", tmp);
    num_tmp = strtol(tmp, NULL, 16);
    yylval.int_val = num_tmp;
    free(tmp);
    return HEXA_LITERAL;
}

[#]+.*[\n] ;
[\t ]+ ;
%%
