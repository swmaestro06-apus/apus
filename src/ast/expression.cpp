#include "ast/expression.h"
#include "ast/value/value.h"

#include "vm/variable_table.h"
#include "vm/context.h"

#include "vm/function_table.h"

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
        cout << "[Variable Expression] var name " << name << endl;
    }

    VariableExpression::VariableExpression(char *name)
        : VariableExpression(std::string(name)) {
    }

    VariableExpression::~VariableExpression() {

    }

    std::shared_ptr<Value> VariableExpression::Evaluate(Context &context) {
        cout << "[Variable Expression] EVALUATE " << name_ << endl;
        return context.FindVariable(name_)->GetValue();
    }


    std::shared_ptr<Variable> VariableExpression::getVariable(Context& context) {
        return context.FindVariable(name_);
    }

    // AssignExpression::

    AssignExpression::AssignExpression(Type type,
                                       std::shared_ptr<Expression> var_expr,
                                       std::shared_ptr<Expression> expression)
        : Expression(type), var_expr_(var_expr), expression_(expression) {

    }

    AssignExpression::AssignExpression(Type type,
                                       Expression* var_expr,
                                       Expression* expression)
        : AssignExpression(type, std::shared_ptr<Expression>(var_expr),
                           std::shared_ptr<Expression>(expression)) {
    }

    AssignExpression::~AssignExpression() {

    }

    std::shared_ptr<Value> AssignExpression::Evaluate(Context &context) {

        if (expression_ != nullptr) {

            // Find left value from the variable table
            std::shared_ptr<Value> left = var_expr_->Evaluate(context);
            std::shared_ptr<Value> right = expression_->Evaluate(context);

            if (left != nullptr && right != nullptr) {

                std::shared_ptr<Value> right_promoted = right->Promote(left);

                if (right_promoted != nullptr) {

                    std::shared_ptr<Value> result =
                            left->OperateBinary(this->getType(), right_promoted);

                    // TODO : and, put 'result' value into the variable
                    std::shared_ptr<Variable> var = std::dynamic_pointer_cast<VariableExpression>(var_expr_)->getVariable(context);
                    var->SetValue(result);

                    return result;
                }
            }
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

    // FunctionExpression::

    FunctionExpression::FunctionExpression(std::string func_name)
            : Expression(EXP_FUNCTION), func_name_(func_name) {

    }

    FunctionExpression::FunctionExpression(char* func_name)
            : FunctionExpression(std::string(func_name)) {
    }

    FunctionExpression::~FunctionExpression() {

    }

    std::shared_ptr<Value> FunctionExpression::Evaluate(Context &context) {

        std::shared_ptr<Function> function = context.FindFunction(func_name_);
        std::shared_ptr<Value> result = nullptr;

        if (function != nullptr) {
            function->Execute(context);
            result = context.GetReturnValue();
        }

        return result;
    }
}
