#include "ast/value/unsigned_int_value.h"
#include "ast/value/signed_int_value.h"
#include "ast/value/character_value.h"
#include "ast/value/float_value.h"
#include "ast/value/string_value.h"

#include "common/common.h"

namespace apus {

    std::shared_ptr<UnsignedIntValue> UnsignedIntValue::Create(TypeSpecifier type, uint64_t value) {

        if (type == U8 || type == U16 || type == U32 || type == U64) {
            return std::shared_ptr<UnsignedIntValue>(new UnsignedIntValue(type, value));
        }

        return nullptr;

    }

    std::shared_ptr<Value> UnsignedIntValue::Promote(
            const std::shared_ptr<Value> another) const {

        const TypeSpecifier another_type = another->getType();

        if (type_ == another->getType()) {
            return this->Copy();
        }

        // case 1. Exactly same type
        if (type_ == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case C8:
            case C16:
            case C32:
            case S8:
            case S16:
            case S32:
            case S64:
            case U8:
            case U16:
            case U32:
            case U64: {

                TypeSpecifier return_type = getSize() > another->getSize() ? getType() : another_type;

                if (S8 <= return_type && return_type <= S64) {
                    return SignedIntValue::Create(return_type, this->getUIntValue());
                }
                else if (C8 <= return_type && return_type <= C32) {
                    return CharacterValue::Create(return_type, this->getUIntValue());
                }
                else if (U8 <= return_type && return_type <= U32) {
                    return UnsignedIntValue::Create(return_type, this->getUIntValue());
                }

                return nullptr;
            }

            case F32:
            case F64: {
                double double_value = static_cast<double>(this->getUIntValue());
                return FloatValue::Create(another_type, double_value);
            }

            case STR8:
            case STR16:
            case STR32: {
                uint64_t uint_value = this->getUIntValue();
                return StringValue::Create(another_type, std::to_string(uint_value));
            }

            default:
                return nullptr;
        }

    }

    std::shared_ptr<Value> UnsignedIntValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right_promoted) const {

        std::shared_ptr<Value> result = nullptr;

        // 'right' value MUST be same type with this's type;
        if (right_promoted->getType() == this->getType()) {

            std::shared_ptr<UnsignedIntValue> right_dynamic = std::dynamic_pointer_cast<UnsignedIntValue>(right_promoted);

            uint64_t left_value = this->getUIntValue();
            uint64_t right_value = right_dynamic->getUIntValue();

            uint64_t result_value = 0;

            switch (expression_type) {

                case Expression::Type::EXP_OR :
                    result_value = left_value | right_value;
                    break;
                case Expression::Type::EXP_AND :
                    result_value = left_value & right_value;
                    break;

                case Expression::Type::EXP_EQL :
                    result_value = left_value == right_value;
                    break;
                case Expression::Type::EXP_NEQ :
                    result_value = left_value != right_value;
                    break;
                case Expression::Type::EXP_LSS :
                    result_value = left_value < right_value;
                    break;
                case Expression::Type::EXP_GTR :
                    result_value = left_value > right_value;
                    break;
                case Expression::Type::EXP_LEQ :
                    result_value = left_value <= right_value;
                    break;
                case Expression::Type::EXP_GEQ :
                    result_value = left_value >= right_value;
                    break;

                case Expression::Type::EXP_LSHIFT :
                case Expression::Type::EXP_LSASSIGN :
                    result_value = left_value << right_value;
                    break;
                case Expression::Type::EXP_RSHIFT :
                case Expression::Type::EXP_RSASSIGN :
                    result_value = left_value >> right_value;
                    break;

                case Expression::Type::EXP_ADD :
                case Expression::Type::EXP_ADDASSIGN :
                    result_value = left_value + right_value;
                    break;
                case Expression::Type::EXP_SUB :
                case Expression::Type::EXP_SUBASSIGN :
                    result_value = left_value - right_value;
                    break;
                case Expression::Type::EXP_MUL :
                case Expression::Type::EXP_MULASSIGN :
                    result_value = left_value * right_value;
                    break;
                case Expression::Type::EXP_DIV :
                case Expression::Type::EXP_DIVASSIGN :
                    result_value = left_value / right_value;
                    break;
                case Expression::Type::EXP_MOD :
                case Expression::Type::EXP_MODASSIGN :
                    result_value = left_value % right_value;
                    break;
                case Expression::Type::EXP_XOR :
                case Expression::Type::EXP_XORASSIGN :
                    result_value = left_value ^ right_value;
                    break;

                case Expression::Type::EXP_LOR :
                    result_value = left_value || right_value;
                    break;
                case Expression::Type::EXP_LAND :
                    result_value = left_value && right_value;
                    break;

                default:
                    return nullptr;
            }

            result = UnsignedIntValue::Create(this->getType(), result_value);
        }

        return result;
    }

    std::shared_ptr<Value> UnsignedIntValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;
        uint64_t result_value = 0;

        switch (expression_type) {
            case Expression::Type::EXP_NOT :
                result_value = !(this->getUIntValue());
                break;
            case Expression::Type::EXP_REVERSE :
                result_value = ~(this->getUIntValue());
                break;
            case Expression::Type::EXP_SUB :
                result_value = -(this->getUIntValue());
                break;
            case Expression::Type::EXP_ADD :
                result_value = +(this->getUIntValue());
                break;

            default:
                return nullptr;
        }

        result = UnsignedIntValue::Create(this->getType(), result_value);

        return result;
    }

}
