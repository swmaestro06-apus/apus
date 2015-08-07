#include "ast/value/character_value.h"

namespace apus {

    std::shared_ptr<Value> CharacterValue::Promote(
            const std::shared_ptr<Value> another) const {

        if (type_ == another->getType()) {
            return this->Copy();
        }

        return nullptr;
    }

    std::shared_ptr<Value> CharacterValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

    std::shared_ptr<Value> CharacterValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

}
