#ifndef CHARACTER_VALUE_H_
#define CHARACTER_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class CharacterValue : public Value {
    public:

        static std::shared_ptr<CharacterValue> Create(TypeSpecifier type , int32_t value);

        virtual ~CharacterValue() {}

        virtual std::shared_ptr<Value> Copy() const {
            return CharacterValue::Create(this->getType(), getCharValue());
        }

        virtual std::shared_ptr<Value> Promote(
                const std::shared_ptr<Value> another) const override;

        virtual std::shared_ptr<Value> OperateBinary(
                const Expression::Type expression_type,
                const std::shared_ptr<Value>& right) const override;

        virtual std::shared_ptr<Value> OperateUnary(
                const Expression::Type expression_type) const override;

        int32_t getCharValue() const {
            return *((int32_t *)value_.get());
        }

    protected:

        CharacterValue(TypeSpecifier type, int32_t value)
                : Value(type, std::make_shared<int32_t>(value)) {
        }

        CharacterValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
                : Value(type, value_ptr) {
        }

    };

}

#endif
