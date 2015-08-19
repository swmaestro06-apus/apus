#include "ast/value/signed_int_value.h"
#include "ast/expression.h"
#include "common/common.h"

#include "ast/value/float_value.h"

namespace apus {

    std::shared_ptr<Value> SignedIntValue::Promote(
            const std::shared_ptr<Value> another) const {

        // PROMOTE THIS, NOT another

        // case 1. Exactly same type
        if (type_ == another->getType()) {
            return this->Copy();
        }

        // case 2. Same class but size
        std::shared_ptr<SignedIntValue> another_dynamic = nullptr;
        if ( (another_dynamic = std::dynamic_pointer_cast<SignedIntValue>(another)) ) {

            TypeSpecifier type = getType() > another_dynamic->getType()
                       ? getType()
                       : another_dynamic->getType();

            return std::make_shared<SignedIntValue>(type, this->getValue());
        }

        // case 3. Different class
        else {

            // case 3.1 FloatValue
            std::shared_ptr<FloatValue> another_fv = nullptr;
            if( (another_fv = std::dynamic_pointer_cast<FloatValue>(another)) ) {

                double value = static_cast<double>(this->getIntValue());
                return std::make_shared<FloatValue>(F64, value);
            }

        }

        return nullptr;
    }

    std::shared_ptr<Value> SignedIntValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right_promoted) const {

        std::shared_ptr<Value> result = nullptr;

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

            result = std::make_shared<SignedIntValue>(this->getType(), result_value);
        }

        return result;
    }

    std::shared_ptr<Value> SignedIntValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;
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

        result = std::make_shared<SignedIntValue>(this->getType(), result_value);

        return result;
    }

}
