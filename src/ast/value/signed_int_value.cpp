#include <ast/expression.h>
#include "ast/value/signed_int_value.h"

namespace apus {

    std::shared_ptr<Value> SignedIntValue::Operate(
            const Expression::Type expression_type,
            const std::shared_ptr<Value> &right) const {

        // Promote
        std::shared_ptr<Value> left_promoted = this->Promote(*right);
        std::shared_ptr<Value> right_promoted = right->Promote(*this);

        // Simple operation
        if (left_promoted != nullptr
            && right_promoted != nullptr
            && left_promoted->getType() == right_promoted->getType()
            && left_promoted->getSize() == right_promoted->getSize()) {

            int64_t left_value = dynamic_cast<SignedIntValue *>(left_promoted.get())->getValue();
            int64_t right_value = dynamic_cast<SignedIntValue *>(right_promoted.get())->getValue();

            int64_t result_value = 0;
            int64_t result_size = left_promoted->getSize();

            switch (expression_type) {

                case Expression::Type::EXP_ADD :
                    result_value = left_value + right_value;
                    break;
                case Expression::Type::EXP_SUB :
                    result_value = left_value - right_value;
                    break;
                case Expression::Type::EXP_MUL :
                    result_value = left_value * right_value;
                    break;
                case Expression::Type::EXP_DIV :
                    result_value = left_value / right_value;
                    break;
                case Expression::Type::EXP_MOD :
                    result_value = left_value % right_value;
                    break;

                default:
                    return nullptr;
            }

            return std::make_shared<SignedIntValue>(result_value, result_size);

        }

        return nullptr;
    }

    std::shared_ptr<Value> SignedIntValue::Promote(
            const Value& another) const {

        return nullptr;
    }

}
