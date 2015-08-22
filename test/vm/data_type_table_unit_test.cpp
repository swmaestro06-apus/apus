#include "gtest/gtest.h"
#include "common/common.h"
#include "vm/data_type_table.h"
using namespace apus;

std::shared_ptr<DataTypeTable> g_dtt = std::make_shared<DataTypeTable>();

TEST(data_type_test, initialization) {
    ASSERT_TRUE(g_dtt != NULL);
    g_dtt->SetPrimitiveTypes();
   
    // Check primitive types to be in data type table
    for (int i = U8; i <= STR32; i++) {
        ASSERT_TRUE(g_dtt->Find((TypeSpecifier)i) != NULL);
    }
}

// struct struct1 {
//     S32 integer1
//     S16 integer2
//     F32 float1
// }
TEST(data_type_test, simple_struct_test) {
    
    DataType* struct1 = new DataType(STRUCT);    
    struct1->Insert("integer1", g_dtt->Find(U8));
    struct1->Insert("integer2", g_dtt->Find(S16));
    struct1->Insert("float1", g_dtt->Find(F32));
    EXPECT_TRUE(struct1->HasChild());
    
    g_dtt->Insert("struct1", struct1);
}

// struct child_struct {
//     U64 unsigned1
//     U32 unsigned2
//     C16 char1
// }
//
// struct parent_struct {
//     C8 char2
//     struct child_struct child1
// }
TEST(data_type_test, struct_in_struct_test) {
    
    DataType* childStruct = new DataType(STRUCT);
    childStruct->Insert("unsigned1", g_dtt->Find(U64));
    childStruct->Insert("unsigned2", g_dtt->Find(U32));
    childStruct->Insert("char1", g_dtt->Find(C16));
    EXPECT_TRUE(childStruct->HasChild());
    
    DataType* parentStruct = new DataType(STRUCT);
    parentStruct->Insert("char2", g_dtt->Find(C8));
    parentStruct->Insert("child_struct", childStruct);
    EXPECT_TRUE(parentStruct->HasChild());
    
    g_dtt->Insert("parent_struct", parentStruct);
}

// struct struct2 {
//     U64 unsigned1
//     U32 unsigned2
//     C16 char1
// }
TEST(data_type_test, Find_test) {
    
    DataType* struct2 = new DataType(STRUCT);
    struct2->Insert("unsigned1", g_dtt->Find(U64));
    struct2->Insert("unsigned2", g_dtt->Find(U32));
    struct2->Insert("char1", g_dtt->Find(C16));
    EXPECT_TRUE(struct2->HasChild());
    
    // things which can be found in this data type
    EXPECT_TRUE(struct2->Find("unsigned1") != NULL);
    EXPECT_TRUE(struct2->Find("unsigned2") != NULL);
    EXPECT_TRUE(struct2->Find("char1") != NULL);
    // things which cannot be found in this data type
    EXPECT_TRUE(struct2->Find("not_exist") == NULL);
    
    g_dtt->Insert("struct2", struct2);
}

// struct struct_with_array {
//     U16[3][4] array1
// }
TEST(data_type_test, array_test) {
    
    ArrayDataType* array = new ArrayDataType(ARRAY);
    array->AddDimension(4);
    array->AddDimension(3);
    array->SetElement(g_dtt->Find(U16));
    EXPECT_EQ(array->GetArraySize(), 3*4);
    EXPECT_EQ(array->GetByteSize(), 3*4*2);
    
    DataType* struct_with_array = new DataType(STRUCT);
    struct_with_array->Insert("array1", array);
    
    g_dtt->Insert("struct_with_array", struct_with_array);
}

// struct struct_with_struct_array {
//     struct struct1[2] struct_array
// }
TEST(data_type_test, struct_array_test) {
    
    // copy "struct1" structure from data type table
    ArrayDataType* childStruct = new ArrayDataType(STRUCT_ARRAY);
    childStruct->AddDimension(2);
    childStruct->SetElement(g_dtt->Find("struct1"));
    
    DataType* struct_with_struct_array = new DataType(STRUCT);
    struct_with_struct_array->Insert("struct_array", childStruct);
    EXPECT_TRUE(struct_with_struct_array->HasChild());
    
    g_dtt->Insert("struct_with_struct_array", struct_with_struct_array);
}

TEST(data_type_table_test, Find_test) {
    
    std::shared_ptr<DataType> struct1 = g_dtt->Find("struct1");
    std::shared_ptr<DataType> parent_struct = g_dtt->Find("parent_struct");
    std::shared_ptr<DataType> struct_with_array 
        = g_dtt->Find("struct_with_array");
    std::shared_ptr<DataType> struct_with_struct_array 
        = g_dtt->Find("struct_with_struct_array");

    ASSERT_TRUE(struct1 != NULL);
    EXPECT_TRUE(struct1->Find("integer1") != NULL);
    EXPECT_TRUE(struct1->Find("integer2") != NULL);
    EXPECT_TRUE(struct1->Find("float1") != NULL);

    ASSERT_TRUE(parent_struct != NULL);
    EXPECT_TRUE(parent_struct->Find("char2") != NULL);
    std::shared_ptr<DataType> child_struct 
        = parent_struct->Find("child_struct");
    ASSERT_TRUE(child_struct != NULL);
    EXPECT_TRUE(child_struct->Find("unsigned1") != NULL);
    EXPECT_TRUE(child_struct->Find("unsigned2") != NULL);
    EXPECT_TRUE(child_struct->Find("char1") != NULL);

    ASSERT_TRUE(struct_with_array != NULL);
    ArrayDataType* array1 = dynamic_cast<ArrayDataType*>
            (struct_with_array->Find("array1").get());
    ASSERT_TRUE(array1 != NULL);
    EXPECT_TRUE(array1->IsArray() == true);

    ASSERT_TRUE(struct_with_struct_array != NULL);
    EXPECT_TRUE(struct_with_struct_array->Find("struct_array") != NULL);
    ArrayDataType* struct_array = dynamic_cast<ArrayDataType*>
            (struct_with_struct_array->Find("struct_array").get());
    EXPECT_TRUE(struct_array->IsArray());
}
