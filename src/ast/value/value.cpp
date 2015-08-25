#include "ast/value/value.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"
#include "ast/value/unsigned_int_value.h"
#include "ast/value/character_value.h"
#include "ast/value/string_value.h"

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
                return (std::dynamic_pointer_cast<UnsignedIntValue>(value)->getUIntValue() != 0);

            case C8:
            case C16:
            case C32:
                return (std::dynamic_pointer_cast<CharacterValue>(value)->getCharValue() != 0);

            case F32:
            case F64:
                return (std::dynamic_pointer_cast<FloatValue>(value)->getFloatValue() != 0);

            case STR8:{
                char val = std::dynamic_pointer_cast<StringValue>(value)->getStringValue()[0];
                return val;
            }
            case STR16: {
                char16_t val = std::dynamic_pointer_cast<StringValue>(value)->getU16StringValue()[0];
                return val;
            }
            case STR32: {
                char32_t val = std::dynamic_pointer_cast<StringValue>(value)->getU32StringValue()[0];
                return val;
            }

            default:
                return false;
        }
    }

}
