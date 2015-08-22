#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>

#include "ast/expression.h"
#include "common/common.h"

namespace apus {

    class Value;
    typedef std::shared_ptr<Value> ValuePtr;

    class Value {
    public:

        virtual ~Value(){}

        virtual TypeSpecifier getType() const { return type_; };

        virtual std::shared_ptr<void> getValue() const { return value_; }

        int getSize() const { return TypeLength(type_); }

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

        Value(TypeSpecifier type, std::shared_ptr<void> value)
                : type_(type), value_(value) {}

        TypeSpecifier           type_;
        std::shared_ptr<void>   value_;

    };

}

#endif
