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

                case Expression::Type::EXP_ASSIGN :
                    result_value = right_value;
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

                default:
                    return nullptr;
            }

            result = CharacterValue::Create(this->getType(), result_value);
        }

        return result;
    }

    std::shared_ptr<Value> CharacterValue::OperateUnary(
            const Expression::Type expression_type) const {

        return nullptr;
    }

}
