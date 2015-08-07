#include <math.h>
#include "ast/value/float_value.h"
#include "ast/value/signed_int_value.h"

namespace apus {

    std::shared_ptr<Value> FloatValue::Promote(
            const std::shared_ptr<Value> another) const {

        // case 1. Exactly same type
        if (type_ == another->getType()) {
            return this->Copy();
        }

        // case 2. Same class but size
        std::shared_ptr<FloatValue> another_dynamic = nullptr;
        if ( (another_dynamic = std::dynamic_pointer_cast<FloatValue>(another)) ) {

            TypeSpecifier type = getType() > another_dynamic->getType()
                                 ? getType()
                                 : another_dynamic->getType();

            return std::make_shared<FloatValue>(type, this->getValue());
        }

        // case 3. Different class
        else {

            // case 3.1 SignedIntValue
            std::shared_ptr<SignedIntValue> another_siv = nullptr;
            if( (another_siv = std::dynamic_pointer_cast<SignedIntValue>(another)) ) {

                return this->Copy();
            }

        }

        return nullptr;
    }

    std::shared_ptr<Value> FloatValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right_promoted) const {

        std::shared_ptr<Value> result = nullptr;

        // 'right' value MUST be same type with this's type;
        if (right_promoted->getType() == this->getType()) {

            std::shared_ptr<FloatValue> right_dynamic = std::dynamic_pointer_cast<FloatValue>(right_promoted);

            double left_value = this->getFloatValue();
            double right_value = right_dynamic->getFloatValue();

            double result_value = 0;
            TypeSpecifier type = this->getType();

            switch (expression_type) {

                case Expression::Type::EXP_OR :
                    return nullptr;
                case Expression::Type::EXP_AND :
                    return nullptr;

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
                    return nullptr;
                case Expression::Type::EXP_RSHIFT :
                    return nullptr;

                case Expression::Type::EXP_ADD :
                    result_value = left_value + right_value;
                    break;
                case Expression::Type::EXP_SUB :
                    result_value = left_value - right_value;
                    break;
                case Expression::Type::EXP_MUL :
                    result_value = left_value * right_value;
                    break;
                case Expression::Type::EXP_DIV :
                    result_value = left_value / right_value;
                    break;
                case Expression::Type::EXP_MOD :
                    result_value = fmod(left_value, right_value);
                    break;
                case Expression::Type::EXP_XOR :
                    return nullptr;

                case Expression::Type::EXP_LOR :
                    result_value = left_value || right_value;
                    break;
                case Expression::Type::EXP_LAND :
                    result_value = left_value && right_value;
                    break;

                default:
                    return nullptr;
            }

            result = std::make_shared<FloatValue>(type, result_value);
        }

        return result;
    }

    std::shared_ptr<Value> FloatValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;
        double result_value = 0;

        switch (expression_type) {
            case Expression::Type::EXP_NOT :
                result_value = !(this->getFloatValue());
                break;
            case Expression::Type::EXP_REVERSE :
                // reverse operation not supported
                return nullptr;
            case Expression::Type::EXP_SUB :
                result_value = -(this->getFloatValue());
                break;
            case Expression::Type::EXP_ADD :
                result_value = +(this->getFloatValue());
                break;

            default:
                return nullptr;
        }

        result = std::make_shared<FloatValue>(this->getType(), result_value);

        return result;
    }

}
