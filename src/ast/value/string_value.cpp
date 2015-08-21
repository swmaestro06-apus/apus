#include "ast/value/string_value.h"
#include "ast/value/float_value.h"
#include "ast/value/character_value.h"
#include "ast/value/signed_int_value.h"

namespace apus {


    std::shared_ptr<StringValue> StringValue::Create(TypeSpecifier type, std::string value) {

        if (type == STR8 || type == STR16 || type == STR32) {
            return std::shared_ptr<StringValue>(new StringValue(type, value));
        }

        return nullptr;
    }

    static std::shared_ptr<StringValue> Create(TypeSpecifier type, char* value) {
        return StringValue::Create(type, std::string(value));
    }

    std::shared_ptr<Value> StringValue::Promote(
            const std::shared_ptr<Value> another) const {

        const TypeSpecifier another_type = another->getType();

        if (type_ == another->getType()) {
            return this->Copy();
        }

        switch (another_type) {
            case STR8 :
            case STR16:
            case STR32: {
                // Compare with 'Type'
                TypeSpecifier return_type = getType() > another_type
                                            ? getType()
                                            : another_type;
                std::string str_value = this->getStringValue();
                return StringValue::Create(return_type, str_value);
            }

            case F32:
            case F64:
            case C8:
            case C16:
            case C32:
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

    std::shared_ptr<Value> StringValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right_promoted) const {

        std::shared_ptr<Value> result = nullptr;

        if (right_promoted->getType() == this->getType()) {

            std::shared_ptr<StringValue> right_dynamic = std::dynamic_pointer_cast<StringValue>(right_promoted);

            std::string left_value = this->getStringValue();
            std::string right_value = right_dynamic->getStringValue();

            std::string result_value = std::string("");

            switch (expression_type) {

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

                case Expression::Type::EXP_ADD :
                case Expression::Type::EXP_ADDASSIGN :
                    result_value = left_value + right_value;
                    break;

                default:
                    return nullptr;
            }

            result = StringValue::Create(this->getType(), result_value);
        }

        return result;
    }

    std::shared_ptr<Value> StringValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

}
