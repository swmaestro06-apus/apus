#include "ast/statement/expression_statement.h"
#include "ast/expression.h"

#include "vm/context.h"

namespace apus {

    ExpressionStatement::ExpressionStatement(
            std::shared_ptr<Expression> expression)
            : expression_(expression) {

    }

    ExpressionStatement::ExpressionStatement(Expression* expression) {
        ExpressionStatement(std::shared_ptr<Expression>(expression));
    }

    ExpressionStatement::~ExpressionStatement() {

    }

    void ExpressionStatement::Execute(Context& context) {
        expression_->Evaluate(context);
    }
}
