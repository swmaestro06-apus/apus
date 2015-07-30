#ifndef SIGNED_INT_VALUE_H_
#define SIGNED_INT_VALUE_H_

#include <memory>
#include "value.h"

namespace apus {

    class SignedIntValue : public Value {
    public:
        SignedIntValue(int64_t value, int size = 64)
            : value_(value), Value(size) { }

        virtual ~SignedIntValue() {}

        virtual Type getType() const override {
            return Signed;
        }

        virtual std::shared_ptr<Value> Copy() const override {
            return std::make_shared<SignedIntValue>(value_, size_);
        }

        int64_t getValue() { return value_; }

        virtual std::shared_ptr<Value> OperateADD(
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateSUB(
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateMUL(
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateDIV(
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateMOD(
                const std::shared_ptr<Value>& right) const override;

    protected:
        int64_t value_;
    };

}

#endif