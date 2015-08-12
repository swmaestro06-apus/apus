#include "ast/statement/jump_statement.h"
#include "ast/statement/for_statement.h"
#include "vm/context.h"

namespace apus {

    BreakStatement::BreakStatement(
            std::shared_ptr<ForStatement> loop_statement)
        : loop_statement_(loop_statement) {
    }

    BreakStatement::BreakStatement(ForStatement *loop_statement) {
        BreakStatement( std::shared_ptr<ForStatement>(loop_statement) );
    }

    BreakStatement::~BreakStatement() {

    }

    void BreakStatement::Execute(Context& context) {
        loop_statement_->Break();
    }


    ContinueStatement::ContinueStatement(
            std::shared_ptr<ForStatement> loop_statement)
        : loop_statement_(loop_statement) {

    }

    ContinueStatement::ContinueStatement(ForStatement *loop_statement) {
        ContinueStatement( std::shared_ptr<ForStatement>(loop_statement) );
    }

    ContinueStatement::~ContinueStatement() {

    }

    void ContinueStatement::Execute(Context& context) {
        loop_statement_->Continue();
    }


    ReturnStatement::ReturnStatement() : expression_(nullptr) {

    }

    ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expression)
        : expression_(expression) {

    }

    ReturnStatement::ReturnStatement(Expression *expression) {
        ReturnStatement( std::shared_ptr<Expression>(expression) );
    }

    ReturnStatement::~ReturnStatement() {

    }

    void ReturnStatement::Execute(Context& context) {

    }

}
