#include "ast/value/string_value.h"

namespace apus {

    std::shared_ptr<Value> StringValue::Promote(
            const std::shared_ptr<Value> another) const {

        if (type_ == another->getType()) {
            return this->Copy();
        }

        return nullptr;
    }

    std::shared_ptr<Value> StringValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

    std::shared_ptr<Value> StringValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

}
