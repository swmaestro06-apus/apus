#include "ast/statement/jump_statement.h"
#include "ast/statement/for_statement.h"
#include "vm/context.h"

namespace apus {

    void BreakStatement::Execute(Context& context) {
        context.SetBreak(true);
    }

    void ContinueStatement::Execute(Context& context) {
        context.SetContinue(true);
    }

    ReturnStatement::ReturnStatement()
        : expression_(nullptr) {

    }

    ReturnStatement::ReturnStatement(ExprPtr expression)
        : expression_(expression) {

    }

    ReturnStatement::ReturnStatement(Expression *expression)
        : ReturnStatement( ExprPtr(expression) ) {
    }

    void ReturnStatement::Execute(Context& context) {

        if (expression_) {
            expression_->Evaluate(context);
        }

        context.SetReturn(true);
    }

    ExitStatement::ExitStatement(ExprPtr expression)
        : expression_(expression) {

    }

    ExitStatement::ExitStatement(Expression *expression)
        : ExitStatement( ExprPtr(expression) ) {
    }

    void ExitStatement::Execute(Context &context) {

        if (expression_) {
            expression_->Evaluate(context);
        }

        context.SetExit(true);
    }

}
