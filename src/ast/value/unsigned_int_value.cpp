#include "ast/value/unsigned_int_value.h"
#include "ast/value/signed_int_value.h"
#include "ast/value/character_value.h"
#include "ast/value/float_value.h"
#include "ast/value/string_value.h"

#include "common/common.h"

namespace apus {

    std::shared_ptr<UnsignedIntValue> UnsignedIntValue::Create(DataTypePtr data_type, uint64_t value) {

        TypeSpecifier type = data_type->GetType();
        if (type == U8 || type == U16 || type == U32 || type == U64) {
            return std::shared_ptr<UnsignedIntValue>(new UnsignedIntValue(data_type, value));
        }

        return nullptr;

    }

    std::shared_ptr<Value> UnsignedIntValue::Promote(
            const std::shared_ptr<Value> another) const {

        const TypeSpecifier another_type = another->getType();

        // case 1. Exactly same type
        if (getType() == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case U8:
            case U16:
            case U32:
            case U64: {
                DataTypePtr return_type = getSize() > another->getSize() ? data_type_ : another->getDataType();
                TypeSpecifier type = return_type->GetType();
                return UnsignedIntValue::Create(return_type, this->getUIntValue());
            }

            case S8:
            case S16:
            case S32:
            case S64: {

                if (getSize() >= another->getSize()) {
                    return UnsignedIntValue::Create(data_type_, this->getUIntValue());
                }
                else {
                    return SignedIntValue::Create(another->getDataType(), this->getUIntValue());
                }
            }

            case F32:
            case F64: {
                double double_value = static_cast<double>(this->getUIntValue());
                return FloatValue::Create(another->getDataType(), double_value);
            }

            case STR8: {
                std::string val = std::to_string(this->getUIntValue());
                return StringValue::Create(another->getDataType(), val);
            }
            case STR16: {
                std::u16string val;
                val += this->getUIntValue();
                return StringValue::CreateU16(another->getDataType(), val);
            }
            case STR32: {
                std::u32string val;
                val += this->getUIntValue();
                return StringValue::CreateU32(another->getDataType(), val);
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

            result = UnsignedIntValue::Create(data_type_, result_value);
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

        result = UnsignedIntValue::Create(data_type_, result_value);

        return result;
    }

}
