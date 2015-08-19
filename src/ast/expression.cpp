#include "ast/expression.h"
#include "ast/value/value.h"
#include "vm/context.h"

namespace apus {

    // Expression::

    Expression::Expression(Type type)
        : type_(type){
    }

    Expression::~Expression() {

    }

    // BinaryExpression::

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

    // UnaryExpression::

    UnaryExpression::UnaryExpression(std::shared_ptr<Expression> expression)
        : Expression(EXP_UNARY), expression_(expression) {

    }

    UnaryExpression::UnaryExpression(Expression* expression)
        : Expression(EXP_UNARY), expression_(expression) {

        std::shared_ptr<Expression> shared_expr(expression);
        expression_ = shared_expr;

    }

    UnaryExpression::~UnaryExpression() {

    }

    std::shared_ptr<Value> UnaryExpression::Evaluate(Context& context) {

        std::shared_ptr<Value> result = nullptr;
        result = expression_->Evaluate(context);

        return result;
    }

    // ValueExpression::

    ValueExpression::ValueExpression(std::shared_ptr<Value> value)
        : Expression(EXP_VALUE), value_(value) {

    }

    ValueExpression::ValueExpression(Value *value) {
        ValueExpression(std::shared_ptr<Value>(value));
    }

    std::shared_ptr<Value> ValueExpression::Evaluate(Context &context) {
        return value_;
    }

    // VariableExpression

    VariableExpression::VariableExpression(std::string name)
        : Expression(EXP_VARIABLE), name_(name) {
    }

    VariableExpression::VariableExpression(char *name) {
        VariableExpression(std::string(name));
    }

    VariableExpression::~VariableExpression() {

    }

    std::shared_ptr<Value> VariableExpression::Evaluate(Context &context) {
        std::shared_ptr<Value> result = nullptr;

        // find variable

        return result;
    }

    // AssignExpression::

    AssignExpression::AssignExpression(std::string name,
                                       std::shared_ptr<Expression> expression)
        : Expression(EXP_ASSIGN), name_(name), expression_(expression) {

    }

    AssignExpression::AssignExpression(char* name, Expression* expression) {
        AssignExpression(std::string(name), std::shared_ptr<Expression>(expression));
    }

    AssignExpression::~AssignExpression() {

    }

    std::shared_ptr<Value> AssignExpression::Evaluate(Context &context) {

        std::shared_ptr<Value> result = nullptr;

        return result;
    }

    // MemberExpression::

    MemberExpression::MemberExpression(std::string parent_name,
                                       std::string child_name)
        : Expression(EXP_MEMBER), parent_name_(parent_name), child_name_(child_name) {

    }

    MemberExpression::MemberExpression(char* parent_name, char* child_name) {
        MemberExpression(std::string(parent_name), std::string(child_name));
    }

    MemberExpression::~MemberExpression() {

    }

    std::shared_ptr<Value> MemberExpression::Evaluate(Context &context) {

        std::shared_ptr<Value> result = nullptr;

        // find variable member

        return result;
    }
}
