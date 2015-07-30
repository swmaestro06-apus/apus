#ifndef CHARACTER_VALUE_H_
#define CHARACTER_VALUE_H_

#include <memory>
#include "value.h"

namespace apus {

    class CharacterValue : public Value {
    public:
        CharacterValue(int32_t value, int size)
            : value_(value), Value(size) {}

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

}

#endif