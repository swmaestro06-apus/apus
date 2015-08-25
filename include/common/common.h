#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <iostream>
#include <stdint.h>
#include <inttypes.h>

namespace apus {

    #define ERROR_MSG   true

    typedef char byte;

    typedef enum {
        NOT_SET,
        LITTLE = 0x04030201ul,
        BIG = 0x01020304ul,
    } Endian;

    typedef enum {
        U8, U16, U32, U64,  // Unsigned Integer
        S8, S16, S32, S64,  // Signed Integer
        F32, F64,           // Floating Point Real Number
        C8, C16, C32,       // Character Type
        STR, STR8, STR16, STR32, // String Type
        STRUCT, UNION,      // Struct and Union
        ARRAY,              // Array
        STRUCT_ARRAY,       // Struct Array
        USER_DEFINED,       // User-defined type
        NOT_DEFINED,        // Not-defined type
    } TypeSpecifier;

    const std::string type_to_string[NOT_DEFINED+1] = {
        "U8", "U16", "U32", "U64",
        "S8", "S16", "S32", "S64",
        "F32", "F64",
        "C8", "C16", "C32",
        "STR", "STR8", "STR16", "STR32",
        "STRUCT", "UNION",
        "ARRAY",
        "STRUCT_ARRAY",
        "USER_DEFINED",
        "NOT_DEFINED",
    };

    int TypeLength (TypeSpecifier type);

    inline int HostEndian() {

        union {
            char bytes[4];
            int value;
        } HostOrder = {{1, 2, 3, 4}};

        return HostOrder.value;
    }

    inline void DispErr(std::string err) {
        if (ERROR_MSG) {
            std::cout << err << std::endl;
        }
    }
}

#endif

