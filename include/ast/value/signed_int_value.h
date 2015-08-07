#ifndef SIGNED_INT_VALUE_H_
#define SIGNED_INT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class SignedIntValue : public Value {
    public:
        SignedIntValue(TypeSpecifier type, int64_t value)
            : Value(type, std::make_shared<int64_t>(value)) {
        }

        SignedIntValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
            : Value(type, value_ptr) {
        }

        virtual ~SignedIntValue() {}

        virtual std::shared_ptr<Value> Copy() const override {
            return std::make_shared<SignedIntValue>(type_, value_);
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        inline int64_t getIntValue() const {
            return *((int64_t *)value_.get());
        }

    };

}

#endif
