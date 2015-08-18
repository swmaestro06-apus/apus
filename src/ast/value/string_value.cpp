#include "ast/value/string_value.h"

namespace apus {

    std::shared_ptr<Value> StringValue::Operate(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {
        return nullptr;
    }

    std::shared_ptr<Value> StringValue::Promote(
            const Value& another) const {
        return nullptr;
    }

}
