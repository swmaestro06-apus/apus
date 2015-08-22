#include "gtest/gtest.h"
#include "parser_context.h"
#include "vm/virtual_machine.h"

extern int yyparse(apus::ParserContext* pctx);
extern int yy_scan_string(const char *);

// test_x x number is defined sub test
// 1 : corrected test
// 2 : uncorrected test
// 3 : CR test

/*

static char var_def_test_1[] = "\
var u8 a                \n\
var u8 b = 10           \n\
var c8 c = 'a'          \n\
var str d = \"sss\"     \n\
var f32 e = 3.4 + 3.7   \n\
";
static char jump_stmt_test_1[] = "\
continue        \n\
break           \n\
return          \n\
return 10+10    \n\
exit            \n\
exit -1         \n\
";
static char for_stmt_test_1[] = "\
for(i = (32+8)*3/4<<2; i < 10; i += 1) { }  \n\
for(i=10; ; ) { }                           \n\
for( ; i < 10; ) { }                        \n\
for( ; ; i += 1) { }                        \n\
for( ; ; ) { }                              \n\
";
static char if_stmt_test_1[] = "\
if(i < 10) { }      \n\
if(i == 10) {       \n\
    a = 10          \n\
}                   \n\
else {              \n\
    a = 0           \n\
}                   \n\
if(i != 10) {       \n\
    a = 10          \n\
}                   \n\
else if(i == 10) {  \n\
    a = 0           \n\
}                   \n\
else {              \n\
    a = 1           \n\
}                   \n\
";
static char expr_stmt_test_1[] = "\
3 + 4   \n\
3 << 4  \n\
3 ^ 4   \n\
!4      \n\
~4      \n\
";
static char block_stmt_test_1[] = "\
{   var u8 a = 7        \n\
    if(a=1) { }         \n\
    else if(b=1) { }    \n\
    else { }            \n\
    for( ; ; ) { }      \n\
    3 * 9               \n\
    return 9            \n\
    exit                \n\
}                       \n\
";
static char if_stmt_test_3[] = "\
if                      \n\
( i == 10 )             \n\
{                       \n\
    var u8 a = 10       \n\
} else if ( j == 10 ) { \n\
    a = 10              \n\
}                       \n\
                        \n\
else { }                \n\
";

TEST (ParserTest, StmtCorrectTest) {
    int result;
    apus::ParserContext pctx;

    yy_scan_string(var_def_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(jump_stmt_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(for_stmt_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(if_stmt_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(expr_stmt_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(block_stmt_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);
}

TEST (ParserTest, StmtLineTest) {
    int result;
    apus::ParserContext pctx;

    yy_scan_string(if_stmt_test_3);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);
}
*/

static char action_test[] = "continue\nbreak\n continue\n break\n continue \n continue\n";
static char action_test2[] = "{ continue\n break \n continue \n } \n";
static char action_test3[] = " if ( 3 > 2 ) { break\n } else { break\n } \n";
static char action_test4[] = " for (3;3;3) { if ( 3+2 * 4 == 7 + 4 ) { break\n } else { break\n } } \n";

apus::ParserContext pctx;

TEST (ParserTest, ActionTest) {
    int result;
    yy_scan_string(action_test4);

    std::shared_ptr<apus::VirtualMachine> vm = std::make_shared<apus::VirtualMachine>();
    pctx.setVM(vm);
    result = yyparse(&pctx);

    vm->Run();

    EXPECT_EQ (result, 0);
}
