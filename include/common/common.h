#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <inttypes.h>

typedef char byte;

enum Endian {
    LITTLE,
    BIG,
};

enum TypeSpecifier {
    U8, U16, U32, U64,  // Unsigned Integer
    S8, S16, S32, S64,  // Signed Integer
    F32, F64,           // Floating Point Real Number
    C8, C16, C32,       // Character Type
    STR8, STR16, STR32, // String Type
};

typedef enum TypeSpecifier VarType;

int TypeLength (VarType type);

#endif

