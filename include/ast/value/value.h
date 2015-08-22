#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>

#include "ast/expression.h"
#include "common/common.h"

namespace apus {

    class Value {
    public:

        virtual ~Value(){}

        virtual TypeSpecifier getType() const { return type_; };

        virtual std::shared_ptr<void> getValue() const { return value_; }

        int getSize() const { return TypeLength(type_); }

        // Deep Copy function
        inline virtual std::shared_ptr<Value> Copy() const { return nullptr; }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const = 0;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const = 0;

        virtual std::shared_ptr<Value> OperateUnary(
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
