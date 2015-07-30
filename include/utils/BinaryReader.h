#ifndef __BINARY_READER_H__
#define __BINARY_READER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdint.h>
#include "common/common.h"
using namespace std;

class BinaryReader
{
public:
    BinaryReader ();
    BinaryReader (string file_name);
    BinaryReader (string file_name, int default_endian);
    ~BinaryReader ();

    void SetDefaultEndian (int default_endian);
    int GetDefaultEndian ();

    // Return an unsigned integer read in input binary file
    uint64_t ReadUInt (streampos offset, int type);
    uint64_t ReadUInt (int type);

    // Return an signed integer read in input binary file
    int64_t ReadInt (streampos offset, int type);
    int64_t ReadInt (int type);

    // Return an real number read in input binary file
    double ReadReal (streampos offset, int type);
    double ReadReal (int type);

    // Return a character read in binary file
    char* ReadChar (streampos offset, int type);
    char* ReadChar (int type);

    // Return a string read in binary file
    char* ReadString (streampos offset, int type);
    char* ReadString (int type);

private:
    char* file_name_;       // file name
    int default_endian_;    // default endian
    ifstream file_stream_;  // file stream to read

    // Returns byte array in specified endian manner
    byte* ConvertEndian(byte* bytes, int length, int endian);

    // Reads binary file and Returns a byte array
    byte* ReadBytes(long offset, int type); 
    byte* ReadBytes(int type);
};

#endif
