#include "ast/statement/expression_statement.h"
#include "ast/expression.h"

#include "vm/context.h"

namespace apus {

    ExpressionStatement::ExpressionStatement(
            ExprPtr expression)
            : expression_(expression) {

    }

    ExpressionStatement::ExpressionStatement(Expression* expression)
      : ExpressionStatement(ExprPtr(expression)) {
    }

    ExpressionStatement::~ExpressionStatement() {

    }

    void ExpressionStatement::Execute(Context& context) {
        if (expression_) {
            expression_->Evaluate(context);
        }
    }
}
