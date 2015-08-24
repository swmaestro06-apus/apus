#ifndef STRING_VALUE_H_
#define STRING_VALUE_H_

#include <string>
#include <memory>

#include "value.h"
#include "common/common.h"

namespace apus {

    class Value;

    class StringValue : public Value {
    public:

        static std::shared_ptr<StringValue> Create(DataTypePtr data_type, std::string value);
        static std::shared_ptr<StringValue> CreateU16(DataTypePtr data_type, std::u16string value);
        static std::shared_ptr<StringValue> CreateU32(DataTypePtr data_type, std::u32string value);

        virtual ~StringValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            switch (data_type_->GetType()) {
                case STR8:
                    return StringValue::Create(data_type_, getStringValue());
                case STR16:
                    return StringValue::CreateU16(data_type_, getU16StringValue());
                case STR32:
                    return StringValue::CreateU32(data_type_, getU32StringValue());
                default:
                    return nullptr;
            }
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        std::string getStringValue() const {
            return *((std::string *)value_.get());
        }

        std::u16string getU16StringValue() const {
            return *((std::u16string *)value_.get());
        }

        std::u32string getU32StringValue() const {
            return *((std::u32string *)value_.get());
        }

        char* getCharPtr() const {
            return (char *)value_.get();
        }

    protected:

        StringValue(DataTypePtr data_type, std::string value)
                : Value(data_type, std::make_shared<std::string>(value)) {

        }

        StringValue(DataTypePtr data_type, std::u16string value)
                : Value(data_type, std::make_shared<std::u16string>(value)) {

        }

        StringValue(DataTypePtr data_type, std::u32string value)
                : Value(data_type, std::make_shared<std::u32string>(value)) {

        }

        StringValue(DataTypePtr data_type, std::shared_ptr<void> value_ptr)
                : Value(data_type, value_ptr) {
        }

        template<class T> T StringOperate(Expression::Type expression_type, T left, T right) const;

    };

}

#endif
