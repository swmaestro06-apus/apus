#ifndef __COMMON_H__
#define __COMMON_H__

typedef char byte;

enum Endian {
    LITTLE, 
    BIG,
};

enum TypeSpecifier {
    U8, U16, U32, U64,          // Unsigned Integer
    S8, S16, S32, S64,          // Signed Integer 
    C8, C16, C32, C64,          // Character Type
    STR8, STR16, STR32, STR64,  // String Type
    F32,                        // Floating Point 32bit (Float)
    F64,                        // Floating Point 64bit (Double)
};

int TypeLength (int type);

#endif
