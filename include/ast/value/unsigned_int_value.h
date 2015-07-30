#ifndef UNSIGNED_INT_VALUE_H_
#define UNSIGNED_INT_VALUE_H_

#include <memory>
#include "signed_int_value.h"

namespace apus {

    class UnsignedIntValue : public SignedIntValue {
    public:
        UnsignedIntValue(uint64_t value, int size)
            : SignedIntValue(value, size) {}

        virtual ~UnsignedIntValue() {}

        virtual Type getType() const {
            return Unsigned;
        }

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<UnsignedIntValue>(value_, size_);
        }

        uint64_t getValue() {
            return value_;
        }

    };

}

#endif