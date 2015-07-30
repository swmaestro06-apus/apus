#include "common/common.h"
#include "utils/BinaryReader.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <string>
using namespace std;

byte* BinaryReader::ConvertEndian(byte* bytes, int length, int endian) {

    byte* ret_bytes = new byte[length];
    strncpy (ret_bytes, bytes, length);

    // LITTLE ENDIAN converts input bytes in reverse order
    if (endian == LITTLE) {
        for (int i = 0; i < length/2; i++) {
            byte temp = ret_bytes[i];
            ret_bytes[i] = ret_bytes[(length-1)-i];
            ret_bytes[(length-1)-i] = temp;
        }
    }
    return ret_bytes;
}

byte* BinaryReader::ReadBytes(long offset, int type) {
    int length = TypeLength (type);
    byte* mem_block = new char[length];

    // move to the offset
    file_stream_.seekg (offset, ios::beg);
    file_stream_.read (mem_block, length);

    return mem_block;
}

byte* BinaryReader::ReadBytes(int type) {
    int length = TypeLength (type);
    byte* mem_block = new char[length];
    file_stream_.read (mem_block, length);

    return mem_block;
}

BinaryReader::BinaryReader() {
    file_name_ = NULL;
}

BinaryReader::BinaryReader(string file_name) {
    // copy the file name
    file_name_ = new char[file_name.length() + 1];
    strcpy(file_name_, file_name.c_str());

    // set LITTLE endian as the default endian
    default_endian_ = LITTLE;

    // open the file in binary instream manner
    file_stream_.open (file_name_, ios::in | ios::binary);
    if (!file_stream_.is_open()) {
        cout << "There's no file with name: " << file_name << endl;
        exit (-1);
    }
}

BinaryReader::BinaryReader(string file_name, int endian) {
    // copy the file name
    file_name_ = new char[file_name.length() + 1];
    strcpy(file_name_, file_name.c_str());

    // set LITTLE endian as the default endian
    default_endian_ = endian;

    // open the file in binary instream manner
    file_stream_.open (file_name_, ios::in | ios::binary);
    if (!file_stream_.is_open()) {
        cout << "There's no file with name: " << file_name << endl;
        exit (-1);
    }
}

BinaryReader::~BinaryReader () {
    // close file stream
    file_stream_.close();
    // free memory
    delete [] file_name_;
}

void BinaryReader::SetDefaultEndian (int endian) {
    default_endian_ = endian;
}

int BinaryReader::GetDefaultEndian () {
    return default_endian_;
}

uint64_t BinaryReader::ReadUInt (streampos offset, int type) {
	uint64_t ret = 0;
    return ret;
}

uint64_t BinaryReader::ReadUInt (int type) {
	return ReadInt (file_stream_.tellg(), type);
}

int64_t BinaryReader::ReadInt (streampos offset, int type) {
	int64_t ret = 0;
    return ret;
}

int64_t BinaryReader::ReadInt (int type) {
    return ReadInt (file_stream_.tellg(), type);
}

double BinaryReader::ReadReal (streampos offset, int type) {
    double ret_double = 0;
    return ret_double;
}

double BinaryReader::ReadReal (int type) {
	return ReadReal (file_stream_.tellg(), type);
}

char* BinaryReader::ReadChar (streampos offset, int type) {
	int length = TypeLength (type);
    char* ret_char = new char[length];
    return ret_char;
}

char* BinaryReader::ReadChar (int type) {
	return ReadChar (file_stream_.tellg(), type);
}

char* BinaryReader::ReadString (streampos offset, int type) {
    char* ret_str;
    return ret_str;
}

char* BinaryReader::ReadString (int type) {
	return ReadChar (file_stream_.tellg(), type);
}

