#include "ast/expression.h"
#include "ast/value/value.h"
#include "vm/context.h"

namespace apus {

    Expression::Expression(Type type)
        : type_(type){
    }

    Expression::~Expression() {

    }

    BinaryExpression::BinaryExpression(Type type,
                                       std::shared_ptr<Expression> leftExpression,
                                       std::shared_ptr<Expression> rightExpression)
        : Expression(type),
          left_expression_(leftExpression),
          right_expression_(rightExpression) {
    }


    BinaryExpression::BinaryExpression(Type type, Expression* leftExpression,
            Expression* rightExpression) {
        std::shared_ptr<Expression> left(leftExpression);
        std::shared_ptr<Expression> right(rightExpression);
        BinaryExpression(type, left, right);
    }

    BinaryExpression::~BinaryExpression() {

    }

    std::shared_ptr<Value> BinaryExpression::Evaluate(Context& context) {

        std::shared_ptr<Value> result = nullptr;

        std::shared_ptr<Value> lValue = left_expression_->Evaluate(context);
        std::shared_ptr<Value> rValue = right_expression_->Evaluate(context);

        result = lValue->Operate(this->getType(), rValue);

        return result;
    }

    UnaryExpression::UnaryExpression(Type type,
                                     std::shared_ptr<Expression> expression)
        : Expression(type), expression_(expression), value_(nullptr) {

    }

    UnaryExpression::UnaryExpression(Type type,
                                     Expression* expression)
        : Expression(type), expression_(expression), value_(nullptr) {

        std::shared_ptr<Expression> shared_expr(expression);
        expression_ = shared_expr;

    }

    UnaryExpression::UnaryExpression(std::shared_ptr<Value> value)
        : Expression(EXP_NONE), expression_(nullptr), value_(value) {

    }

    UnaryExpression::UnaryExpression(Value* value)
        : Expression(EXP_NONE), expression_(nullptr) {

        std::shared_ptr<Value> shared_value(value);
        value_ = shared_value;

    }

    UnaryExpression::~UnaryExpression() {

    }

    std::shared_ptr<Value> UnaryExpression::Evaluate(Context& context) {

        std::shared_ptr<Value> result = nullptr;

        switch (type_) {
        case EXP_NOT:
            break;
        case EXP_SUB:
            break;
        case EXP_NONE:
            result = value_;
            break;
        default:
            result = expression_->Evaluate(context);
            break;
        }

        return result;
    }
}
