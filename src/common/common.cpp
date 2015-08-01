#include "common/common.h"

int TypeLength (VarType type) {
    int length = 0;
    switch (type) {
       case U8:S8:C8:
           length = 1; 
           break;
       case U16:S16:C16:
           length = 2;
           break;
       case U32:S32:C32:F32:
           length = 4;
           break;
       case U64:S64:C64:F64:
           length = 8;
           break;
       default:
           length = 0;
           break;
    }
    return length;
}
