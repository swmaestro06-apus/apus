#ifndef SIGNED_INT_VALUE_H_
#define SIGNED_INT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class SignedIntValue : public Value {
    public:

        static std::shared_ptr<SignedIntValue> Create(DataTypePtr data_type, int64_t value);

        virtual ~SignedIntValue() {}

        virtual ValuePtr Copy() const override {
            return SignedIntValue::Create(data_type_, getIntValue());
        }

        virtual ValuePtr Promote(const ValuePtr another) const override;

        virtual ValuePtr OperateBinary(
                const Expression::Type expression_type,
                const ValuePtr& right) const override;

        virtual ValuePtr OperateUnary(
                const Expression::Type expression_type) const override;

        inline int64_t getIntValue() const {
            return *((int64_t *)value_.get());
        }

    protected:

        SignedIntValue(DataTypePtr data_type, int64_t value)
                : Value(data_type, std::make_shared<int64_t>(value)) {
        }

        SignedIntValue(DataTypePtr data_type, std::shared_ptr<void> value_ptr)
                : Value(data_type, value_ptr) {
        }

    };

}

#endif
