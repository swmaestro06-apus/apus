#include "common/common.h"
#include "utils/BinaryReader.h"
using namespace std;

BinaryReader::BinaryReader() {

}

BinaryReader::BinaryReader(string& file_name) {

    file_name_.assign (file_name);

    // open the file in binary instream manner
    file_stream_.open (file_name_, ios::in | ios::binary);
    if (!file_stream_.is_open()) {
        cout << "There's no file with name: " << file_name << endl;
        cout << "Program will exit." << endl;
        exit (-1);
    }
}

BinaryReader::~BinaryReader () {

    // close file stream
    file_stream_.close();
}

int BinaryReader::ReadInt (streampos pos, VarType type, uint64_t& out_int) {

    // If it's not proper type, return -1
    if (type != U8 && type != U16 && type != U32 && type != U64 &&
        type != S8 && type != S16 && type != S32 && type != S64) {
        return -1;
    }

    int length = TypeLength(type);
    union {
        char bytes[8];
        uint64_t value;
    } Integer = {{0,}};
   
    // move to the offset POS and read bytes
    file_stream_.seekg (pos, ios::beg);
    file_stream_.read (Integer.bytes, length);

    out_int = Integer.value;
    return 0;
}

int BinaryReader::ReadInt (VarType type, uint64_t& out_int) {

    return ReadInt (file_stream_.tellg(), type, out_int);
}

int BinaryReader::ReadReal (streampos pos, VarType type, double& out_real) {

    // If it's not proper type, return -1
    if (type != F32 && type != F64) {
        return -1;
    }
    
    int length = TypeLength (type);
    union {
        char bytes[8];
        float single_value;
        double double_value;
    } Real = {{0,}};

    // move to the offset POS and read bytes
    file_stream_.seekg (pos, ios::beg);
    file_stream_.read (Real.bytes, length);

    if (type == F32) {
        out_real = (double)Real.single_value;
    } else if (type == F64) {
        out_real = Real.double_value;
    }
    return 0;
}

int BinaryReader::ReadReal (VarType type, double& out_real) {

	return ReadReal (file_stream_.tellg(), type, out_real);
}

int BinaryReader::ReadChar (streampos pos, VarType type, uint32_t& out_char) {

    // If it's not proper type, return -1
    if (type != C8 && type != C16 && type != C32) {
        return -1;
    }
    
    int length = TypeLength (type);
    union {
        char bytes[4];
        uint8_t c8;
        uint16_t c16;
        uint32_t c32;
    } Character = {{0,}};

    // move to the offset POS and read bytes
    file_stream_.seekg (pos, ios::beg);
    file_stream_.read (Character.bytes, length);

    if (type == C8) {
        out_char = (uint32_t) Character.c8;
    } else if (type == C16) {
        out_char = (uint32_t) Character.c16;
    } else if (type == C32) {
        out_char = Character.c32;
    } 
    return 0;
}

int BinaryReader::ReadChar (VarType type, uint32_t& out_char) {

	return ReadChar (file_stream_.tellg(), type, out_char);
}

int BinaryReader::ReadString (streampos pos, VarType type, string& out_str) {

    uint32_t read = 0;                  // read character
    VarType char_type;                  // type of a character

    // assign type of a character
    if (type == STR8) {
        char_type = C8;
    } else if (type == STR16) {
        char_type = C16;
    } else if (type == STR32) {
        char_type = C32;
    } else {
    // If it's not proper type, return -1
        return -1;
    }

    // move to the offset POS
    file_stream_.seekg (pos, ios::beg);
    do {
        if (ReadChar (char_type, read) != 0) {
            // If reading character fails, return -1
            return -1;
        } else {
            // If reading character succeeds, concatenate it to the string
            union {
                char bytes[4];
                uint32_t read;
            } Character;
            Character.read =read;
            out_str.append(Character.bytes);
        }
    } while (read != 0);

    return 0;
}

int BinaryReader::ReadString (VarType type, string& out_char) {

	return ReadString (file_stream_.tellg(), type, out_char);
}

