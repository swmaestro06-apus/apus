#include "ast/value/signed_int_value.h"
#include "ast/value/unsigned_int_value.h"
#include "ast/value/float_value.h"
#include "ast/value/character_value.h"

#include "ast/expression.h"
#include "common/common.h"

namespace apus {

    std::shared_ptr<SignedIntValue> SignedIntValue::Create(DataTypePtr data_type,
                                                           int64_t value) {
        TypeSpecifier type = data_type->GetType();
        if (type == S8 || type == S16 || type == S32 || type == S64) {
            return std::shared_ptr<SignedIntValue>(new SignedIntValue(data_type, value));
        }

        return nullptr;
    }

    ValuePtr SignedIntValue::Promote(const ValuePtr another) const {

        // PROMOTE THIS, NOT another

        const TypeSpecifier another_type = another->getType();

        // case 1. Exactly same type
        if (getType() == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case S8:
            case S16:
            case S32:
            case S64:
            case U8:
            case U16:
            case U32:
            case U64: {
                DataTypePtr return_type = getSize() > another->getSize() ? data_type_ : another->getDataType();
                TypeSpecifier type = return_type->GetType();

                if (S8 <= type && type <= S64) {
                    return SignedIntValue::Create(return_type, this->getIntValue());
                }
                else if (U8 <= type && type <= U32) {
                    return UnsignedIntValue::Create(return_type, this->getIntValue());
                }

                return nullptr;
            }

            // case 3. Different class
            case F32:
            case F64: {
                double double_value = static_cast<double>(this->getIntValue());
                return FloatValue::Create(another->getDataType(), double_value);
            }

            default:
                return nullptr;
        }
    }

    ValuePtr SignedIntValue::OperateBinary(
            const Expression::Type expression_type,
            const ValuePtr &right_promoted) const {

        ValuePtr result = nullptr;

        // 'right' value MUST be same type with this's type;
        if (right_promoted->getType() == this->getType()) {

            std::shared_ptr<SignedIntValue> right_dynamic = std::dynamic_pointer_cast<SignedIntValue>(right_promoted);

            int64_t left_value = this->getIntValue();
            int64_t right_value = right_dynamic->getIntValue();

            int64_t result_value = 0;

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

                case Expression::Type::EXP_ASSIGN :
                    result_value = right_value;
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

            result = SignedIntValue::Create(data_type_, result_value);
        }

        return result;
    }

    ValuePtr SignedIntValue::OperateUnary(
            const Expression::Type expression_type) const {

        ValuePtr result = nullptr;
        int64_t result_value = 0;

        switch (expression_type) {
            case Expression::Type::EXP_NOT :
                result_value = !(this->getIntValue());
                break;
            case Expression::Type::EXP_REVERSE :
                result_value = ~(this->getIntValue());
                break;
            case Expression::Type::EXP_SUB :
                result_value = -(this->getIntValue());
                break;
            case Expression::Type::EXP_ADD :
                result_value = +(this->getIntValue());
                break;

                default:
                    return nullptr;
        }

        result = SignedIntValue::Create(data_type_, result_value);

        return result;
    }

}
