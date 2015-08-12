#ifndef VALUE_H_
#define VALUE_H_

#include <memory>
#include <string>

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

        inline int getSize() { return size_; }

        virtual std::shared_ptr<Value> OperateADD(
                const std::shared_ptr<Value>& right) const { return nullptr; }

        virtual std::shared_ptr<Value> OperateSUB(
                const std::shared_ptr<Value>& right) const { return nullptr; }

        virtual std::shared_ptr<Value> OperateMUL(
                const std::shared_ptr<Value>& right) const { return nullptr; }

        virtual std::shared_ptr<Value> OperateDIV(
                const std::shared_ptr<Value>& right) const { return nullptr; }

        virtual std::shared_ptr<Value> OperateMOD(
                const std::shared_ptr<Value>& right) const { return nullptr; }

    protected:
        int size_;
    };

}

#endif
