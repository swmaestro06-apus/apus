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

        static std::shared_ptr<StringValue> Create(TypeSpecifier type, std::string value);
        static std::shared_ptr<StringValue> Create(TypeSpecifier type, char* value);

        virtual ~StringValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return StringValue::Create(type_, getStringValue());
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

    protected:

        StringValue(TypeSpecifier type, std::string value)
                : Value(type, std::make_shared<std::string>(value)) {}

        StringValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
                : Value(type, value_ptr) {
        }

    };

}

#endif
