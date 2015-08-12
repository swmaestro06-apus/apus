#ifndef FLOAT_VALUE_H_
#define FLOAT_VALUE_H_

#include <memory>
#include "value.h"

namespace apus {

    class FloatValue : public Value {
    public:
        FloatValue(double value, int size)
            : value_(value), Value(size) {}
        virtual ~FloatValue() {}

        virtual Type getType() const {
            return Float;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<FloatValue>(value_, size_);
        }

        virtual std::shared_ptr<Value> Promote(
                const Value& another) const override;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        double getValue() {
            return value_;
        }

    protected:

        double value_;
    };

}

#endif
