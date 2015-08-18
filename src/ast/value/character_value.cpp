#include "ast/value/character_value.h"

namespace apus {

    std::shared_ptr<Value> CharacterValue::Promote(
            const Value& another) const {

        if (type_ == another.getType()) {
            return another.Copy();
        }

        return nullptr;
    }

    std::shared_ptr<Value> CharacterValue::Operate(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {
        return nullptr;
    }

}
