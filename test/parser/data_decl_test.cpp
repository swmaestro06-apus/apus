#include "gtest/gtest.h"

extern int yyparse(void);
extern int yy_scan_string(const char *);

static char data_decl_test[] = "\
struct id {\n\
    u8 aa\n\
    f32 bb = 8\n\
}\n\
\n\
struct id2\n\
{\n\
    s8 aa = 0\n\
    str bb = \"string string\"\n\
}\n\
\n\
struct id3 { c8 aa = 'a' }\n\
\n\
union id4 {\n\
    u8 aa\n\
    f32 bb = 3.8\n\
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

    yy_scan_string(data_decl_test);
    int result = yyparse();

    EXPECT_EQ (result, 0);
}
