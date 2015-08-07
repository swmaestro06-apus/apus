#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>

#include "ast/expression.h"
#include "common/common.h"

namespace apus {

    class Value {
    public:

        Value(TypeSpecifier type) : type_(type) {}
        virtual ~Value(){}

        // returns type of current object
        virtual TypeSpecifier getType() const { return type_; };

        // Deep Copy function
        inline virtual std::shared_ptr<Value> Copy() const { return nullptr; }

        int getSize() const { return TypeLength(type_); }

        virtual std::shared_ptr<Value> Promote(const Value& another) const = 0;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const { return nullptr; }

    protected:

        TypeSpecifier type_;
    };

}

#endif
