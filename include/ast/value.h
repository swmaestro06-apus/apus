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

        virtual std::shared_ptr<Value> OperateAdd(
                const std::shared_ptr<Value>& right) const {return nullptr;}
        virtual std::shared_ptr<Value> OperateSub(
                const std::shared_ptr<Value>& right) const {return nullptr;}
        virtual std::shared_ptr<Value> OperateMul(
                const std::shared_ptr<Value>& right) const {return nullptr;}
        virtual std::shared_ptr<Value> OperateDiv(
                const std::shared_ptr<Value>& right) const {return nullptr;}
        virtual std::shared_ptr<Value> OperateMod(
                const std::shared_ptr<Value>& right) const {return nullptr;}

    protected:
        int size_;
    };

    class SignedValue : public Value {
    public:
        SignedValue(int64_t value, int size = 64) : value_(value), Value(size) { }
        virtual ~SignedValue() {}

        virtual Type getType() const {
            return Signed;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<SignedValue>(value_, size_);
        }

        int64_t getValue() { return value_; }

        virtual std::shared_ptr<Value> OperateAdd(const std::shared_ptr<Value>& right) const;
        virtual std::shared_ptr<Value> OperateSub(const std::shared_ptr<Value>& right) const;
        virtual std::shared_ptr<Value> OperateMul(const std::shared_ptr<Value>& right) const;
        virtual std::shared_ptr<Value> OperateDiv(const std::shared_ptr<Value>& right) const;
        virtual std::shared_ptr<Value> OperateMod(const std::shared_ptr<Value>& right) const;

    protected:
        int64_t value_;
    };

    class UnsignedValue : public SignedValue {
    public:
        UnsignedValue(uint64_t value, int size) : SignedValue(value, size) {}
        virtual ~UnsignedValue() {}

        virtual Type getType() const {
            return Unsigned;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<UnsignedValue>(value_, size_);
        }

        uint64_t getValue() {
            return value_;
        }
    };

    class FloatValue : public Value {
    public:
        FloatValue(double value, int size) : value_(value), Value(size) {}
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

    class CharacterValue : public Value {
    public:
        CharacterValue(int32_t value, int size) : value_(value), Value(size) {}
        virtual ~CharacterValue() {}

        virtual Type getType() const {
            return Character;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<CharacterValue>(value_, size_);
        }

        int32_t getValue() {
            return value_;
        }

    private:
        int32_t value_;
    };

    class StringValue : public Value {
    public:
        StringValue(std::string value, int size) : value_(value), Value(size) {}
        virtual ~StringValue() {}

        virtual Type getType() const {
            return String;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<StringValue>(value_, size_);
        }

        std::string getValue() {
            return value_;
        }
    private:
        std::string value_;
    };

}

#endif
