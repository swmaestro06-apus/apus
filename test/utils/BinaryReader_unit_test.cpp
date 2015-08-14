#include "gtest/gtest.h"
#include "utils/BinaryReader.h"
#include <limits.h>

TEST (BinaryReaderTest, ReadIntUnsignedIntegerTest) {

    string filename = "./test_unsigned_integer.bin";
    unsigned char ff = 0xff;
    FILE *fp = fopen(filename.c_str(), "wb");
    for (int i = 0; i < 15; i++) {
        fwrite (&ff, sizeof(unsigned char), 1, fp);
    }
    fclose (fp);

    uint64_t temp = 0;
    BinaryReader br(filename);

    // Read 8-bit unsigned integer
    uint8_t expected_uint8 = UCHAR_MAX;
    if (br.ReadInt (0, U8, temp) == 0) {
        uint8_t read_uint8 = (uint8_t)temp;
        EXPECT_EQ (read_uint8, expected_uint8);
    }
    // Read 16-bit unsigned integer
    uint16_t expected_uint16 = USHRT_MAX;
    if (br.ReadInt (U16, temp) == 0) {
        uint16_t read_uint16 = (uint16_t)temp;
        EXPECT_EQ (read_uint16, expected_uint16);
    }
    // Read 32-bit unsigned integer
    uint32_t expected_uint32 = UINT_MAX;
    if (br.ReadInt (U32, temp) == 0) {
        uint32_t read_uint32 = (uint32_t)temp;
        EXPECT_EQ (read_uint32, expected_uint32);
    }
    // Read 64-bit unsigned integer
    uint64_t expected_uint64 = ULONG_MAX;
    if (br.ReadInt (U64, temp) == 0) {
        uint64_t read_uint64 = (uint64_t)temp;
        EXPECT_EQ (read_uint64, expected_uint64);
    }
    
    remove (filename.c_str());
}

TEST (BinaryReaderTest, ReadIntSignedIntegerTest) {

    string filename = "./test_signed_integer.bin";
    unsigned char ff = 0xff;
    FILE *fp = fopen(filename.c_str(), "wb");
    for (int i = 0; i < 15; i++) {
        fwrite (&ff, sizeof(unsigned char), 1, fp);
    }
    fclose (fp);

    uint64_t temp = 0;
    BinaryReader br(filename);
    
    // Read 8-bit signed integer
    int8_t expected_int8 = -1;
    if (br.ReadInt (0, U8, temp) == 0) {
        int8_t read_int8 = (int8_t)temp;
        EXPECT_EQ (read_int8, expected_int8);
    }
    // Read 16-bit signed integer
    int16_t expected_int16 = -1;
    if (br.ReadInt (U16, temp) == 0) {
        int16_t read_int16 = (int16_t)temp;
        EXPECT_EQ (read_int16, expected_int16);
    }
    // Read 32-bit signed integer
    int32_t expected_int32 = -1;
    if (br.ReadInt (U32, temp) == 0) {
        int32_t read_int32 = (int32_t)temp;
        EXPECT_EQ (read_int32, expected_int32);
    }
    // Read 64-bit signed integer
    int64_t expected_int64 = -1;
    if (br.ReadInt (U64, temp) == 0) {
        int64_t read_int64 = (int64_t)temp;
        EXPECT_EQ (read_int64, expected_int64);
    }
    remove (filename.c_str());
}

TEST (BinaryReaderTest, ReadRealTest) {

    string filename = "./test_real.bin";
    float expected_single = 10;
    double expected_double = 15;

    FILE *fp = fopen(filename.c_str(), "wb");
    fwrite (&expected_single, sizeof(float), 1, fp);
    fwrite (&expected_double, sizeof(double), 1, fp);
    fclose (fp);

    double temp;
    BinaryReader br(filename);
   
    // Read 32-bit single-precision floating-point number
    if (br.ReadReal (0, F32, temp) == 0) {
        float read_single = (float)temp;
        EXPECT_EQ (read_single, expected_single);
    }
    // Read 64-bit double-precision floating-point number
    if (br.ReadReal (F64, temp) == 0) {
        double read_double = temp; 
        EXPECT_EQ (read_double, expected_double);
    }
    remove (filename.c_str());
}

TEST (BinaryReaderTest, ReadCharTest) {

    string filename = "./test_char.bin";
    union {
        char bytes[4];
        uint8_t c8;
        uint16_t c16;
        uint32_t c32;
    } ExpectedChar = {{'a','b','c','d'}};

    FILE *fp = fopen(filename.c_str(), "wb");
    fwrite (&ExpectedChar, sizeof(ExpectedChar), 1, fp);
    fclose(fp);

    uint32_t temp;
    BinaryReader br(filename);

    // Read 8-bit Character
    if (br.ReadChar (0, C8, temp) == 0) {
        char read_char8 = (char) temp;
        EXPECT_EQ (read_char8, ExpectedChar.c8);
    }
    // Read 16-bit Character
    if (br.ReadChar (0, C16, temp) == 0) {
        uint16_t read_char16 = (uint16_t) temp;
        EXPECT_EQ (read_char16, ExpectedChar.c16);
    }
    // Read 32-bit Character
    if (br.ReadChar (0, C32, temp) == 0) {
        uint32_t read_char32 = (uint32_t) temp;
        EXPECT_EQ (read_char32, ExpectedChar.c32);
    }
    remove(filename.c_str());
}

TEST (BinaryReaderTest, ReadStringTest) {

    string filename = "./test_string.bin";

    char nul = 0x0;
    char *str = "Test Code";
    FILE *fp = fopen(filename.c_str(), "wb");
    fwrite (str, strlen(str), 1, fp);
    fwrite (&nul, sizeof(char), 1, fp);
    fwrite (str, strlen(str), 1, fp);
    fclose (fp);

    string read_str;
    BinaryReader br(filename);
    if (br.ReadString (0, STR8, read_str) == 0) {
        EXPECT_STREQ (str, read_str.c_str());
    }

    remove(filename.c_str());
}

TEST (BinaryReaderTest, EndianTest) {

    string filename = "./test_endian.bin";
    union {
        char bytes[4];
        int integer;
    } Integer = {{1,2,3,4}};

    FILE *fp = fopen(filename.c_str(), "wb");
    fwrite (&Integer, sizeof(Integer), 1, fp);
    fclose (fp);

    int expected_big = 0x01020304ul;
    int expected_little = 0x04030201ul;

    BinaryReader br (filename);
    uint64_t read = 0;
    // Set the reverse endian of host system to the file endian
    if (HostEndian() == LITTLE) {

        br.SetFileEndian (BIG);
        if (br.ReadInt(0, S32, read) == 0) {
            EXPECT_EQ ((int)read, expected_big);
        }
    } else if (HostEndian() == BIG) {

        br.SetFileEndian (LITTLE);
        if (br.ReadInt (0, S32, read) == 0) {
            EXPECT_EQ ((int)read, expected_little);
        }
    }
}

