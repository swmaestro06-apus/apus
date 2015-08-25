#include "ast/value/string_value.h"
#include "ast/value/float_value.h"
#include "ast/value/character_value.h"
#include "ast/value/signed_int_value.h"

namespace apus {

    std::shared_ptr<StringValue> StringValue::Create(DataTypePtr data_type, std::string value) {

        TypeSpecifier type = data_type->GetType();
        if (type == STR8) {
            return std::shared_ptr<StringValue>(new StringValue(data_type, value));
        }
        return nullptr;
    }

    std::shared_ptr<StringValue> StringValue::CreateU16(DataTypePtr data_type, std::u16string value) {

        TypeSpecifier type = data_type->GetType();
        if (type == STR16) {
            return std::shared_ptr<StringValue>(new StringValue(data_type, value));
        }
        return nullptr;
    }

    std::shared_ptr<StringValue> StringValue::CreateU32(DataTypePtr data_type, std::u32string value) {

        TypeSpecifier type = data_type->GetType();
        if (type == STR32) {
            return std::shared_ptr<StringValue>(new StringValue(data_type, value));
        }
        return nullptr;
    }

    std::shared_ptr<Value> StringValue::Promote(
            const std::shared_ptr<Value> another) const {

        const TypeSpecifier another_type = another->getType();

        if (getType() == another_type) {
            return this->Copy();
        }

        switch (another_type) {

            case STR8 : {
                return this->Copy();
            }
            case STR16: {

                switch (getType()) {
                    case STR8:
                        return StringValue::CreateU16(another->getDataType(), Utf8To16(getStringValue()));
                    case STR32:
                        return this->Copy();
                    default:
                        return nullptr;
                }
            }
            case STR32: {

                switch (getType()) {
                    case STR8:
                        return StringValue::CreateU32(another->getDataType(), Utf8To32(getStringValue()));
                    case STR16:
                        return StringValue::CreateU32(another->getDataType(), Utf16To32(getU16StringValue()));
                    default:
                        return nullptr;
                }
            }

            case F32:
            case F64:
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

            switch (data_type_->GetType()) {
                case STR8:{
                    std::string left_value = this->getStringValue();
                    std::string right_value = right_dynamic->getStringValue();
                    std::string result_value = StringOperate<std::string>(expression_type, left_value, right_value);
                    result = StringValue::Create(data_type_, result_value);
                    break;
                }
                case STR16:{
                    std::u16string left_value = this->getU16StringValue();
                    std::u16string right_value = right_dynamic->getU16StringValue();
                    std::u16string result_value = StringOperate<std::u16string>(expression_type, left_value, right_value);
                    result = StringValue::CreateU16(data_type_, result_value);
                    break;
                }
                case STR32:{
                    std::u32string left_value = this->getU32StringValue();
                    std::u32string right_value = right_dynamic->getU32StringValue();
                    std::u32string result_value = StringOperate<std::u32string>(expression_type, left_value, right_value);
                    result = StringValue::CreateU32(data_type_, result_value);
                    break;
                }

                default:
                    return nullptr;
            }

        }

        return result;
    }

    template<class T>
    T StringValue::StringOperate(Expression::Type expression_type,
                                 T left_value,
                                 T right_value) const {
        T result_value;

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

        return result_value;
    }

    std::shared_ptr<Value> StringValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

    std::u16string StringValue::Utf8To16(std::string string) const {
        const char* str_data = string.data();
        std::u16string result = u"";

        while (*str_data) {
            char16_t c = static_cast<char16_t>(*str_data);
            result += c;
            str_data++;
        }
        return result;
    }

    std::u32string StringValue::Utf8To32(std::string string) const {
        const char* str_data = string.data();
        std::u32string result = U"";

        while (*str_data) {
            char32_t c = static_cast<char32_t>(*str_data);
            result += c;
            str_data++;
        }
        return result;
    }

    std::u32string StringValue::Utf16To32(std::u16string string) const {
        const char16_t* str_data = string.data();
        std::u32string result = U"";

        while (*str_data) {
            char32_t c = static_cast<char32_t>(*str_data);
            result += c;
            str_data++;
        }
        return result;
    }
}
