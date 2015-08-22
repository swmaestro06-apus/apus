#include "ast/value/value.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"

namespace apus {

    bool Value::IsTrue(std::shared_ptr<Value> value) {

        switch (value->getType()) {
            case S8:
            case S16:
            case S32:
            case S64:
                return (std::dynamic_pointer_cast<SignedIntValue>(value)->getIntValue() != 0);

            case U8:
            case U16:
            case U32:
            case U64:
                return false;

            case C8:
            case C16:
            case C32:
                return false;

            case F32:
            case F64:
                return (std::dynamic_pointer_cast<FloatValue>(value)->getFloatValue() != 0);

            case STR8:
            case STR16:
            case STR32:

            default:
                return false;
        }
    }

}
