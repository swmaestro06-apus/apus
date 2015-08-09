#include "gtest/gtest.h"

extern "C" int yyparse(void);
extern "C" FILE *yyin;
static char data_decl_test[] = "\
struct id {\n\
    u8 aa\n\
    f32 bb = 8 + -1\n\
}\n\
\n\
struct id2\n\
{\n\
    s8 aa = (4+1)-1 * 3 % 4 << 3 >> 29 * 0\n\
    str bb = \"string string\"\n\
}\n\
\n\
struct id3 { c8 aa = 'a' }\n\
\n\
union id4 {\n\
    u8 aa\n\
    f32 bb = 3.8 * 9\n\
}\n\
\n\
union id5\n\
{\n\
    u8 aa\n\
    struct id bb\n\
}\n\
\n\
\n\
union id6 { u32 aa }\n\
";

TEST (ParserTest, DataDeclTest) {
    FILE *testfile = fmemopen(data_decl_test, sizeof(data_decl_test), "r");
    yyin = testfile;
    int result = yyparse();

    EXPECT_EQ (result, 0);
}
