%{
#include <stdio.h>
#include "y.tab.hh"
%}

%option noyywrap
%option yylineno

%%
"u8"    { return U8; }
"u16"   { return U16; }
"u32"   { return U32; }
"u64"   { return U64; }
"s8"    { return S8; }
"s16"   { return S16; }
"s32"   { return S32; }
"s64"   { return S64; }
"f32"   { return F32; }
"f64"   { return F64; }
"c8"    { return C8; }
"c16"   { return C16; }
"c32"   { return C32; }
"str"   { return STR; }
"str8"  { return STR8; }
"str16" { return STR16; }
"str32" { return STR32; }
"var"   { return VAR; }

"include" { return INCLUDE; }
"union"   { return UNION; }
"struct"  { return STRUCT; }
"const"   { return CONST; }
"if"      { return IF; }
"else"    { return ELSE; }
"for"     { return FOR; }
"return"  { return RETURN; }
"exit"    { return EXIT; }
"true"    { return TRUE; }
"false"   { return FALSE; }

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

"{"  { return L_BRACE; }
"}"  { return R_BRACE; }
"["  { return L_CASE; }
"]"  { return R_CASE; }
"("  { return OPEN; }
")"  { return CLOSE; }
"\n" { return CR; }

[1-9][0-9]* {
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
[a-z]+[0-9a-z_]* {
    yylval.str_val = (char*)malloc(yyleng);
    sprintf(yylval.str_val, "%s", yytext);
    // Sting control : yytext[NUM] 
    return ID;
}

'([^'\n|\\'])'     { return CHAR_LITERAL; }
\"([^"\n]|\\\")*\" { return STRING_LITERAL; }

[#]+.*[\n] ;
[\t ]+ ;
%%
