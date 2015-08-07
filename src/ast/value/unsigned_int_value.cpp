#include "ast/value/unsigned_int_value.h"
#include "common/common.h"

namespace apus {

    std::shared_ptr<Value> UnsignedIntValue::Promote(
            const std::shared_ptr<Value> another) const {

        if (type_ == another->getType()) {
            return this->Copy();
        }

        return nullptr;
    }

    std::shared_ptr<Value> UnsignedIntValue::OperateBinary(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {

        std::shared_ptr<SignedIntValue> result = std::dynamic_pointer_cast<SignedIntValue>(SignedIntValue::OperateBinary(expression_type, right));

        TypeSpecifier type = TypeSpecifier::U64;
        uint64_t uval = (uint64_t) result->getIntValue();

        std::shared_ptr<UnsignedIntValue> result_unsigned = std::make_shared<UnsignedIntValue>(type, uval);

        return result_unsigned;
    }

    std::shared_ptr<Value> UnsignedIntValue::OperateUnary(
            const Expression::Type expression_type) const {

        std::shared_ptr<Value> result = SignedIntValue::OperateUnary(expression_type);

        return result;
    }

}
