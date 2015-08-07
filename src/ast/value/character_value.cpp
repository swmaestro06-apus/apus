#include "ast/value/character_value.h"

namespace apus {

    std::shared_ptr<Value> CharacterValue::Operate(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {
        return nullptr;
    }

    std::shared_ptr<Value> CharacterValue::Promote(
            const Value& another) const {
        return nullptr;
    }

}
