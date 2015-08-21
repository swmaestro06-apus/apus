#include "gtest/gtest.h"
#include "common/common.h"
#include "vm/data_type_table.h"
using namespace apus;

std::shared_ptr<DataTypeTable> g_dtt = std::make_shared<DataTypeTable>();

// struct struct1 {
//     S32 integer1
//     S16 integer2
//     F32 float1
// }
TEST(data_type_test, simple_struct_test) {

    DataType* struct1 = new DataType(STRUCT, "struct1");
    struct1->Insert(new DataType(S32, "integer1"));
    struct1->Insert(new DataType(S16, "integer2"));
    struct1->Insert(new DataType(F32, "float1"));
    EXPECT_TRUE(struct1->HasChild());

    g_dtt->Insert(struct1);
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

    DataType* childStruct = new DataType(STRUCT, "child_struct");
    childStruct->Insert(new DataType(U64, "unsigned1"));
    childStruct->Insert(new DataType(U32, "unsigned2"));
    childStruct->Insert(new DataType(C16, "char1"));
    EXPECT_TRUE(childStruct->HasChild());

    DataType* parentStruct = new DataType(STRUCT, "parent_struct");
    parentStruct->Insert(new DataType(C8, "char2"));
    parentStruct->Insert(childStruct);
    EXPECT_TRUE(parentStruct->HasChild());

    g_dtt->Insert(parentStruct);
}

// struct struct2 {
//     U64 unsigned1
//     U32 unsigned2
//     C16 char1
// }
TEST(data_type_test, Find_test) {
    
    DataType* struct2 = new DataType(STRUCT, "struct2");
    struct2->Insert(new DataType(U64, "unsigned1"));
    struct2->Insert(new DataType(U32, "unsigned2"));
    struct2->Insert(new DataType(C16, "char1"));
    EXPECT_TRUE(struct2->HasChild());
    
    // things which can be found in this data type
    EXPECT_TRUE(struct2->Find(0) != NULL);
    EXPECT_TRUE(struct2->Find("unsigned2") != NULL);
    // things which cannot be found in this data type
    EXPECT_TRUE(struct2->Find("not_existed") == NULL);

    g_dtt->Insert(struct2);
}

// struct struct_with_array {
//     U8[3][4] array1
// }
TEST(data_type_test, array_test) {
    
    DataType* array = new DataType("array1");
    array->AddDimension(3);
    array->AddDimension(4);
    array->SetType(U8);
    EXPECT_EQ(array->GetArraySize(), 3*4);
    EXPECT_EQ(array->GetByteSize(), 3*4*1);

    DataType* struct_with_array = new DataType(STRUCT, "struct_with_array");
    struct_with_array->Insert(array);

    g_dtt->Insert(struct_with_array);
}

// struct struct_with_struct_array {
//     struct struct1[2] struct_array
// }
TEST(data_type_test, struct_array_test) {
    
    // copy "struct1" structure from data type table
    DataType* childStruct = new DataType(STRUCT);
    childStruct->Copy(g_dtt->Find("struct1").get());
    childStruct->SetName("struct_array");
    childStruct->AddDimension(2);
    EXPECT_TRUE(childStruct->HasChild());

    DataType* struct_with_struct_array = new DataType(STRUCT);
    struct_with_struct_array->SetName("struct_with_struct_array");
    struct_with_struct_array->Insert(childStruct);
    EXPECT_TRUE(struct_with_struct_array->HasChild());
    std::cout << struct_with_struct_array->GetArraySize() << std::endl;
    std::cout << struct_with_struct_array->GetByteSize() << std::endl;

    g_dtt->Insert(struct_with_struct_array);
}

TEST(data_type_table_test, Find_test) {

    EXPECT_TRUE(g_dtt->Find("struct1") != NULL);
    EXPECT_TRUE(g_dtt->Find("parent_struct") != NULL);
    EXPECT_TRUE(g_dtt->Find("struct2") != NULL);
    EXPECT_TRUE(g_dtt->Find("struct_with_array") != NULL);
    EXPECT_TRUE(g_dtt->Find("struct_with_struct_array") != NULL);
}
