#ifndef UNSIGNED_INT_VALUE_H_
#define UNSIGNED_INT_VALUE_H_

#include <memory>
#include "signed_int_value.h"

namespace apus {

    class UnsignedIntValue : public SignedIntValue {
    public:
        UnsignedIntValue(TypeSpecifier type, uint64_t value)
            : SignedIntValue(type, value) {}

        virtual ~UnsignedIntValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<UnsignedIntValue>(type_, value_);
        }

        virtual std::shared_ptr<Value> Promote(
                const Value& another) const override;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        uint64_t getValue() {
            return value_;
        }

    protected:

    };

}

#endif
