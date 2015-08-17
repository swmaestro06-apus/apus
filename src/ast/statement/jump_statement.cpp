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

    ReturnStatement::ReturnStatement() : expression_(nullptr) {

    }

    ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expression)
        : expression_(expression) {

    }

    ReturnStatement::ReturnStatement(Expression *expression) {
        ReturnStatement( std::shared_ptr<Expression>(expression) );
    }

    void ReturnStatement::Execute(Context& context) {
        context.SetReturn(true);
    }

    ExitStatement::ExitStatement(std::shared_ptr<Expression> expression)
        : expression_(expression) {

    }

    ExitStatement::ExitStatement(Expression *expression) {
        ExitStatement( std::shared_ptr<Expression>(expression) );
    }

    void ExitStatement::Execute(Context &context) {
        context.SetExit(true);
    }

}
