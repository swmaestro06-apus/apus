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
            Expression* rightExpression)
    
        : BinaryExpression(type,
                           std::shared_ptr<Expression>(leftExpression),
                           std::shared_ptr<Expression>(rightExpression)) {

    }

    BinaryExpression::~BinaryExpression() {

    }

    std::shared_ptr<Value> BinaryExpression::Evaluate(Context& context) {

        std::shared_ptr<Value> result = nullptr;

        // 1. check expression
        if (left_expression_ != nullptr && right_expression_ != nullptr) {

            std::shared_ptr<Value> left_value = left_expression_->Evaluate(context);
            std::shared_ptr<Value> right_value = right_expression_->Evaluate(context);

            // 2. check lvalue, rvalue
            if (left_value != nullptr && right_value != nullptr) {

                std::shared_ptr<Value> left_promoted = left_value->Promote(right_value);
                std::shared_ptr<Value> right_promoted = right_value->Promote(left_value);

                // 3. check promoted values
                if (left_promoted != nullptr && right_promoted != nullptr) {

                    result = left_promoted->OperateBinary(this->getType(),
                                                          right_promoted);
                }

            }

        }

        return result;
    }

    // UnaryExpression::

    UnaryExpression::UnaryExpression(Type type, std::shared_ptr<Expression> expression)
        : Expression(type), expression_(expression) {

    }

    UnaryExpression::UnaryExpression(Type type, Expression* expression)

        : UnaryExpression(type, std::shared_ptr<Expression>(expression)) {
    }

    UnaryExpression::~UnaryExpression() {

    }

    std::shared_ptr<Value> UnaryExpression::Evaluate(Context& context) {

        std::shared_ptr<Value> result = nullptr;
        result = expression_->Evaluate(context);
        result = result->OperateUnary(this->getType());

        return result;
    }

    // ValueExpression::

    ValueExpression::ValueExpression(std::shared_ptr<Value> value)
        : Expression(EXP_VALUE), value_(value) {

    }

    ValueExpression::ValueExpression(Value *value)
        : ValueExpression(std::shared_ptr<Value>(value)) {
    }

    std::shared_ptr<Value> ValueExpression::Evaluate(Context &context) {
        return value_;
    }

    // VariableExpression

    VariableExpression::VariableExpression(std::string name)
        : Expression(EXP_VARIABLE), name_(name) {
    }

    VariableExpression::VariableExpression(char *name)
        : VariableExpression(std::string(name)) {
    }

    VariableExpression::~VariableExpression() {

    }

    std::shared_ptr<Value> VariableExpression::Evaluate(Context &context) {
        std::shared_ptr<Value> result = nullptr;

        // find variable

        return result;
    }

    // AssignExpression::

    AssignExpression::AssignExpression(Type type,
                                       std::string name,
                                       std::shared_ptr<Expression> expression)
        : Expression(type), name_(name), expression_(expression) {

    }

    AssignExpression::AssignExpression(Type type, char* name,
                                       Expression* expression)
        : AssignExpression(type, std::string(name), std::shared_ptr<Expression>(expression)) {
    }

    AssignExpression::~AssignExpression() {

    }

    std::shared_ptr<Value> AssignExpression::Evaluate(Context &context) {

        if (expression_ != nullptr) {

            // Find left value from the variable table
            std::shared_ptr<Value> left = nullptr;
            std::shared_ptr<Value> right = expression_->Evaluate(context);

            if (left != nullptr && right != nullptr) {

                std::shared_ptr<Value> right_promoted = right->Promote(left);

                if (right_promoted != nullptr) {

                    std::shared_ptr<Value> result =
                            left->OperateBinary(this->getType(), right_promoted);

                    // and, put 'result' value into the variable

                }
            }
            return left;
        }
        return nullptr;
    }

    // MemberExpression::

    MemberExpression::MemberExpression(std::string parent_name,
                                       std::string child_name)
        : Expression(EXP_MEMBER), parent_name_(parent_name), child_name_(child_name) {

    }

    MemberExpression::MemberExpression(char* parent_name, char* child_name)
        : MemberExpression(std::string(parent_name), std::string(child_name)) {
    }

    MemberExpression::~MemberExpression() {

    }

    std::shared_ptr<Value> MemberExpression::Evaluate(Context &context) {

        std::shared_ptr<Value> result = nullptr;

        // find variable member

        return result;
    }
}
