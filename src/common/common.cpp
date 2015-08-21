#include "common/common.h"
#include <iostream>
using namespace std;

namespace apus {

    int TypeLength(TypeSpecifier type) {
        int length = 0;
        switch (type) {
            case U8:
            case S8:
            case C8:
                length = 1; // 1 byte
                break;

            case U16:
            case S16:
            case C16:
                length = 2; // 2 bytes
                break;

            case U32:
            case S32:
            case C32:
            case F32:
                length = 4; // 4 bytes
                break;

            case U64:
            case S64:
            case F64:
                length = 8; // 8 bytes
                break;

            case STR8:
            case STR16:
            case STR32:
                length = 0; // not fixed. variable-length
                break;
                
            // exception
            default:
                DispErr("There's no matched variable type.");
                length = -1;
                break;
        }
        return length;
    }
}
