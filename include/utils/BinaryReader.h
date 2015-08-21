#ifndef __BINARY_READER_H__
#define __BINARY_READER_H__

#include <iostream>
#include <fstream>
#include "common/common.h"
using namespace std;

namespace apus {

    class BinaryReader {
    public:
        BinaryReader();
        BinaryReader(string &file_name);
        ~BinaryReader();

        Endian GetFileEndian();
        void SetFileEndian(Endian endian);

        int ReadInt(streampos offset, TypeSpecifier type, uint64_t &out_int);
        int ReadInt(TypeSpecifier type, uint64_t &out_int);

        int ReadReal(streampos offset, TypeSpecifier type, double &out_real);
        int ReadReal(TypeSpecifier type, double &out_real);

        int ReadChar(streampos offset, TypeSpecifier type, uint32_t &out_char);
        int ReadChar(TypeSpecifier type, uint32_t &out_char);

        int ReadString(streampos offset, TypeSpecifier type, string &out_str);
        int ReadString(TypeSpecifier type, string &out_str);

    private:
        string file_name_;                  // file name
        ifstream file_stream_;              // file stream to read
        Endian file_endian_;                // endian of file

        int ConvertBytes(byte out_array[], int length);
    };
}

#endif

