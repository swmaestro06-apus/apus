#include "gtest/gtest.h"
#include "parser_context.h"

extern int yyparse(apus::ParserContext* pctx);
#include "vm/virtual_machine.h"

extern int yy_scan_string(const char *);

// test_x x number is defined sub test
// 1 : corrected test
// 2 : uncorrected test
// 3 : CR test

static char one_dimension_test_1[] = "\
var u8[1] aa\n\
var u8[2] bb = [1, 2]\n\
var struct id2[2] cc = [{1, 2}, {3, 4}]\n\
";

static char two_dimension_test_1[] = "\
var u8[1][2] dd\n\
var u8[2][2] ee = [[1, 2], [3, 4]]\n\
var struct id2[2][2] ff = [[{1, 2}, {3, 4}], [{5, 6}, {7, 8}]]\n\
";

static char three_dimension_test_1[] = "\
var u8[1][2][3] gg\n\
var u8[2][2][2] hh = [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]\n\
var struct id2[2][2][2] ii = [[[{1, 2}, {3, 4}], [{5, 6}, {7, 8}]], [[{1, 2}, {3, 4}], [{5, 6}, {7, 8}]]]\n\
";

static char used_array_test_1[] = "\
aa = aa[1][2] + bb\n\
a[1][2] = aa[1][2][3] + bb\n\
";

static char three_dimension_test_3[] = "\
var u8[2] jj = [1,\n\
                2]\n\
var u8[2][2] kk = [[1, 2],\n\
                   [3, 4]]\n\
var struct id2[2][2][2] ll = [[[{1, 2}, {3, 4}], [{5, 6}, {7, 8}]],\n\
                              [[{9, 0}, {1, 2}], [{3, 4}, {5, 6}]]]\n\
";
/*
apus::ParserContext pctx;

TEST (ParserTest, ArrayCorrectTest) {
 
    std::shared_ptr<apus::VirtualMachine> vm = std::make_shared<VirtualMachine>();
    pctx.setVM(vm);

    int result;
    apus::ParserContext pctx;

    yy_scan_string(one_dimension_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(two_dimension_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(three_dimension_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);

    yy_scan_string(used_array_test_1);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);
}

TEST (ParserTest, ArrayCRTest) {
    int result;
    apus::ParserContext pctx;

    yy_scan_string(three_dimension_test_3);
    result = yyparse(&pctx);
    EXPECT_EQ (result, 0);
}

*/
