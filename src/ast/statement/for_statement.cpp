#include "ast/statement/for_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"

namespace apus {

    ForStatement::ForStatement() {

    }

    ForStatement::~ForStatement() {

    }

    void ForStatement::Execute() {
        initialization_->Evaluate();

        while(termination_->Evaluate()){
            body_->Execute();
            increment_->Evaluate();
        }
    }

}
