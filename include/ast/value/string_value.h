#ifndef STRING_VALUE_H_
#define STRING_VALUE_H_

#include <string>
#include <memory>

#include "value.h"

namespace apus {

    class Value;

    class StringValue : public Value {
    public:
        StringValue(std::string value, int size)
            : value_(value), Value(size) {}
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