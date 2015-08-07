#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>
#include "ast/expression.h"

namespace apus {

    class Value {
    public:

        enum Type {
            Signed,
            Unsigned,
            Float,
            Byte,
            Character,
            String,
            UserDefined
        };

        Value(int size = 0) : size_(size) {}
        virtual ~Value(){}

        // returns type of current object
        virtual Type getType() const = 0;

        // Deep Copy function
        inline virtual std::shared_ptr<Value> Copy() const { return nullptr; }

        inline int getSize() const { return size_; }

        virtual std::shared_ptr<Value> Promote(const Value& another) const = 0;

        virtual std::shared_ptr<Value> Operate(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const { return nullptr; }

    protected:

        int size_;
    };

}

#endif
