#include "ast/for_statement.h"
#include "ast/expression.h"
#include "ast/block.h"

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
