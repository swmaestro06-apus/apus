#ifndef CHARACTER_VALUE_H_
#define CHARACTER_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class CharacterValue : public Value {
    public:
        CharacterValue(TypeSpecifier type, int32_t value)
            : Value(type, std::make_shared<int32_t>(value)) {
        }

        CharacterValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
            : Value(type, value_ptr) {
        }

        virtual ~CharacterValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return std::make_shared<CharacterValue>(type_, value_);
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        int32_t getCharacterValue() const {
            return *((int32_t *)value_.get());
        }
    };

}

#endif
