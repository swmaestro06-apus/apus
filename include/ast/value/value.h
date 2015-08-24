#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>

#include "ast/expression.h"
#include "common/common.h"

#include "vm/data_type_table.h"

namespace apus {

    class Value;
    typedef std::shared_ptr<Value> ValuePtr;
    class DataType;
    typedef std::shared_ptr<DataType> DataTypePtr;

    class Value {
    public:

        virtual ~Value(){}

        virtual TypeSpecifier getType() const { return data_type_->GetType(); }

        virtual std::shared_ptr<void> getValue() const { return value_; }

        int getSize() const { return TypeLength(getType()); }

        DataTypePtr getDataType() { return data_type_; }

        // Deep Copy function
        inline virtual ValuePtr Copy() const { return nullptr; }

        virtual ValuePtr Promote(
                const ValuePtr another) const = 0;

        virtual ValuePtr OperateBinary(
                const Expression::Type expression_type,
                const ValuePtr& right) const = 0;

        virtual ValuePtr OperateUnary(
                const Expression::Type expression_type) const = 0;

        static bool IsTrue(std::shared_ptr<Value> value);

    protected:

        Value(DataTypePtr data_type, std::shared_ptr<void> value)
                : data_type_(data_type), value_(value) {}

        DataTypePtr             data_type_;
        std::shared_ptr<void>   value_;

    };

}

#endif
