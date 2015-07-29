#include "for_statement.h"
#include "expression.h"
#include "block.h"

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
