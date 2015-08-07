#ifndef UNSIGNED_INT_VALUE_H_
#define UNSIGNED_INT_VALUE_H_

#include <memory>
#include "signed_int_value.h"

namespace apus {

    class UnsignedIntValue : public SignedIntValue {
    public:
        UnsignedIntValue(TypeSpecifier type, uint64_t value)
            : SignedIntValue(type, value) {}

        UnsignedIntValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
            : SignedIntValue(type, value_ptr) {
        }

        virtual ~UnsignedIntValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<UnsignedIntValue>(type_, value_);
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        uint64_t getUIntValue() const {
            return (uint64_t)SignedIntValue::getIntValue();
        }

    };

}

#endif
