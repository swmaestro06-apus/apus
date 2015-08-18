#ifndef FLOAT_VALUE_H_
#define FLOAT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class FloatValue : public Value {
    public:
        FloatValue(TypeSpecifier type, double value)
            : Value(type), value_(value) {}
        virtual ~FloatValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<FloatValue>(type_, value_);
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
