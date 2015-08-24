#include <cmath>
#include <limits>

#include "ast/value/float_value.h"
#include "ast/value/signed_int_value.h"

namespace apus {

    std::shared_ptr<FloatValue> FloatValue::Create(TypeSpecifier type,
                                                   double value) {
        // check 'type'
        if (type == F32 || type == F64) {
            return std::shared_ptr<FloatValue>(new FloatValue(type, value));
        }

        return nullptr;
    }

    ValuePtr FloatValue::Promote(const ValuePtr another) const {

        const TypeSpecifier another_type = another->getType();

        // case 1. Exactly same type
        if (type_ == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case F32:
            case F64: {
                TypeSpecifier type = getSize() > another->getSize()
                                     ? getType()
                                     : another_type;

                return FloatValue::Create(type, this->getFloatValue());
            }

            case S8:
            case S16:
            case S32:
            case S64: {

                return this->Copy();

            }
            default:
                return nullptr;
        }
        
    }

    ValuePtr FloatValue::OperateBinary(
            const Expression::Type expression_type,
            const ValuePtr &right_promoted) const {

        ValuePtr result = nullptr;

        // 'right' value MUST be same type with this's type;
        if (right_promoted->getType() == this->getType()) {

            double epsilon = std::numeric_limits<double>::epsilon();

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
                    result_value = this->NearlyEqual(right_value);
                    break;
                case Expression::Type::EXP_NEQ :
                    result_value = !this->NearlyEqual(right_value);
                    break;
                case Expression::Type::EXP_LSS :
                    result_value = left_value < right_value;
                    break;
                case Expression::Type::EXP_GTR :
                    result_value = left_value > right_value;
                    break;
                case Expression::Type::EXP_LEQ :
                    result_value = (left_value < right_value) || this->NearlyEqual(right_value);
                    break;
                case Expression::Type::EXP_GEQ :
                    result_value = (left_value > right_value) || this->NearlyEqual(right_value);
                    break;

                case Expression::Type::EXP_ASSIGN :
                    result_value = right_value;
                    break;

                case Expression::Type::EXP_LSHIFT :
                case Expression::Type::EXP_LSASSIGN :
                    return nullptr;
                case Expression::Type::EXP_RSHIFT :
                case Expression::Type::EXP_RSASSIGN :
                    return nullptr;

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
                    result_value = fmod(left_value, right_value);
                    break;
                case Expression::Type::EXP_XOR :
                case Expression::Type::EXP_XORASSIGN :
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

            result = FloatValue::Create(type, result_value);
        }

        return result;
    }

    ValuePtr FloatValue::OperateUnary(
            const Expression::Type expression_type) const {

        ValuePtr result = nullptr;
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

        result = FloatValue::Create(this->getType(), result_value);

        return result;
    }

    double FloatValue::NearlyEqual(double another) const {

        const double a = getFloatValue();
        const double b = another;

        const double absA = std::abs(a);
        const double absB = std::abs(b);
        const double diff = std::abs(a - b);

        const double epsilon = std::numeric_limits<double>::epsilon();

        if (a == b) {
            // shortcut, handles infinities
            return true;
        }
        else if (a == 0 || b == 0 || diff < std::numeric_limits<double>::min()) {
            // a or b is zero or both are extremely close to it
            // relative error is less meaningful here
            return diff < (epsilon * std::numeric_limits<double>::min());
        }
        else { // use relative error
            return diff / std::min((absA + absB), std::numeric_limits<double>::max()) < epsilon;
        }
    }

}
