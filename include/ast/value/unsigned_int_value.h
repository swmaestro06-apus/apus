#ifndef UNSIGNED_INT_VALUE_H_
#define UNSIGNED_INT_VALUE_H_

#include <memory>
#include "signed_int_value.h"

namespace apus {

    class UnsignedIntValue : public Value {
    public:

        static std::shared_ptr<UnsignedIntValue> Create(TypeSpecifier type, uint64_t value);

        virtual ~UnsignedIntValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return UnsignedIntValue::Create(type_, getUIntValue());
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        uint64_t getUIntValue() const {
            return *((uint64_t*)value_.get());
        }

    protected:

        UnsignedIntValue(TypeSpecifier type, uint64_t value)
                : UnsignedIntValue(type, std::make_shared<uint64_t>(value)) {}

        UnsignedIntValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
                : Value(type, value_ptr) {
        }

    };

}

#endif
