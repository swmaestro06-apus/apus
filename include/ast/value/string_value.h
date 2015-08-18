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
        StringValue(TypeSpecifier type, std::string value)
            : Value(type), value_(value) {}
        virtual ~StringValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<StringValue>(type_, value_);
        }

        virtual std::shared_ptr<Value> Promote(
                const Value& another) const override;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        std::string getValue() {
            return value_;
        }

    protected:

        std::string value_;
    };

}

#endif
