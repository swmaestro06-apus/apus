#include "ast/statement/jump_statement.h"
#include "ast/statement/for_statement.h"

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

    void BreakStatement::Execute() {
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

    void ContinueStatement::Execute() {
        loop_statement_->Continue();
    }


    ReturnStatement::ReturnStatement() {

    }

    ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expression) {

    }

    ReturnStatement::ReturnStatement(Expression *expression) {

    }

    ReturnStatement::~ReturnStatement() {

    }

}
