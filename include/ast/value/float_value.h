#ifndef FLOAT_VALUE_H_
#define FLOAT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class FloatValue : public Value {
    public:

        static std::shared_ptr<FloatValue> Create(DataTypePtr data_type, double value);

        virtual ~FloatValue() {}

        virtual ValuePtr Copy() const {
            return FloatValue::Create(data_type_, getFloatValue());
        }
        virtual ValuePtr Promote(const ValuePtr another) const override;

        virtual ValuePtr OperateBinary(
                const Expression::Type expression_type,
                const ValuePtr& right) const override;

        virtual ValuePtr OperateUnary(
                const Expression::Type expression_type) const override;

        double getFloatValue() const {
            return *((double *)value_.get());
        }

    protected:

        double NearlyEqual(double another) const;

        FloatValue(DataTypePtr data_type, double value)
                : Value(data_type, std::make_shared<double>(value)) {
        }

        FloatValue(DataTypePtr data_type, std::shared_ptr<void> value_ptr)
                : Value(data_type, value_ptr) {
        }

    };

}

#endif
