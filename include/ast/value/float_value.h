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

        double getValue() {
            return value_;
        }

    private:
        double value_;
    };

}

#endif