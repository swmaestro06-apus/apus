#include "ast/value/float_value.h"

namespace apus {

    std::shared_ptr<Value> FloatValue::Operate(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {
        return nullptr;
    }

    std::shared_ptr<Value> FloatValue::Promote(
            const Value& another) const {
        return nullptr;
    }
}
