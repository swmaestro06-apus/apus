#ifndef FLOAT_VALUE_H_
#define FLOAT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class FloatValue : public Value {
    public:
        FloatValue(TypeSpecifier type, double value)
            : Value(type, std::make_shared<double>(value)) {
        }

        FloatValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
            : Value(type, value_ptr) {
        }

        virtual ~FloatValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<FloatValue>(type_, value_);
        }
        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        double getFloatValue() const {
            return *((double *)value_.get());
        }

    protected:

        double NearlyEqual(double another) const ;
    };

}

#endif
