#include "ast/value/character_value.h"
#include "ast/value/float_value.h"

namespace apus {

    std::shared_ptr<CharacterValue> CharacterValue::Create(TypeSpecifier type, int32_t value) {

        if (type == C8 || type == C16 || type == C32) {
            return std::shared_ptr<CharacterValue>(new CharacterValue(type, value));
        }

        return nullptr;
    }

    std::shared_ptr<Value> CharacterValue::Promote(
            const std::shared_ptr<Value> another) const {

        const TypeSpecifier another_type = another->getType();

        if (type_ == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case C8:
            case C16:
            case C32: {
                TypeSpecifier return_type = getSize() > another->getSize()
                                            ? getType()
                                            : another_type;

                return CharacterValue::Create(return_type, this->getCharValue());
            }

            default:
                return nullptr;

        }

    }

    std::shared_ptr<Value> CharacterValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right_promoted) const {

        std::shared_ptr<Value> result = nullptr;

        if (right_promoted->getType() == this->getType()) {

            std::shared_ptr<CharacterValue> right_dynamic = std::dynamic_pointer_cast<CharacterValue>(right_promoted);

            int32_t left_value = this->getCharValue();
            int32_t right_value = right_dynamic->getCharValue();

            int32_t result_value = 0;

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

            result = CharacterValue::Create(this->getType(), result_value);
        }

        return result;
    }

    std::shared_ptr<Value> CharacterValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;
        int32_t result_value = 0;

        switch (expression_type) {
            case Expression::Type::EXP_NOT :
                result_value = !(this->getCharValue());
                break;
            case Expression::Type::EXP_REVERSE :
                result_value = ~(this->getCharValue());
                break;
            case Expression::Type::EXP_SUB :
                result_value = -(this->getCharValue());
                break;
            case Expression::Type::EXP_ADD :
                result_value = +(this->getCharValue());
                break;

            default:
                return nullptr;
        }

        result = CharacterValue::Create(this->getType(), result_value);

        return result;
    }

}
