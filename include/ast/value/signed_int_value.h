#ifndef SIGNED_INT_VALUE_H_
#define SIGNED_INT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class SignedIntValue : public Value {
    public:
        SignedIntValue(TypeSpecifier type, int64_t value)
            : Value(type), value_(value) { }

        virtual ~SignedIntValue() {}

        virtual std::shared_ptr<Value> Copy() const override {
            return std::make_shared<SignedIntValue>(type_, value_);
        }

        int64_t getValue() { return value_; }

        virtual std::shared_ptr<Value> Promote(
                const Value& another) const override;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

    protected:

        int64_t value_;
    };

}

#endif
