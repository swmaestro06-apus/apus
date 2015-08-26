#include "gtest/gtest.h"
#include "vm/data_type_table.h"
#include "vm/variable_table.h"
#include "ast/value/value.h"
#include "ast/value/signed_int_value.h"
#include "ast/value/string_value.h"
using namespace apus;

static std::shared_ptr<DataTypeTable> dtt = std::make_shared<DataTypeTable>();
static std::shared_ptr<VariableTable> vt = std::make_shared<VariableTable>();

TEST(variable_test, initialization) {
    ASSERT_TRUE(dtt != NULL);
    dtt->SetPrimitiveTypes();
    
    // Check primitive types to be in data type table
    for (int i = U8; i <= STR32; i++) {
        ASSERT_TRUE(dtt->Find((TypeSpecifier)i) != NULL);
    }
}

// var U8 a
TEST(variable_test, only_declaration_test) {
    VarPtr var = std::make_shared<Variable>("a", dtt->Find(U8));
    ASSERT_TRUE(var != NULL);
    EXPECT_TRUE(var->getType() == U8);

    vt->Insert(var->getName(), var);
}

// var S16 b = 5
TEST(variable_test, init_value_test) {
    VarPtr var = std::make_shared<Variable>("b", dtt->Find(S16));
    std::shared_ptr<SignedIntValue> signed_int_5 
        = SignedIntValue::Create(dtt->Find(S16), 5);
    var->setValue(signed_int_5);

    ASSERT_TRUE(var != NULL);
    EXPECT_TRUE(var->getValue()->IsTrue(signed_int_5));

    vt->Insert(var->getName(), var);
}

// var STR8 c = "Hello"
TEST(variable_test, string_init_test) {
    VarPtr var = std::make_shared<Variable>("c", dtt->Find(STR8));
    std::shared_ptr<StringValue> string_hello 
        = StringValue::Create(dtt->Find(STR8), "Hello");
    var->setValue(string_hello);

    ASSERT_TRUE(var != NULL);
    EXPECT_TRUE(var->getValue()->IsTrue(string_hello));

    vt->Insert(var->getName(), var);
}

TEST(variable_table_test, find_test) {
    std::shared_ptr<Variable> var_a = vt->Find("a");
    std::shared_ptr<Variable> var_b = vt->Find("b");
    std::shared_ptr<Variable> var_c = vt->Find("c");

    ASSERT_TRUE(var_a != NULL);
    ASSERT_TRUE(var_b != NULL);
    ASSERT_TRUE(var_c != NULL);
}
