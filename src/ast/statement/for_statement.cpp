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

        while (termination_->Evaluate()) {
            body_->Execute();

            if (break_) {
                break_ = true;
                break;
            }
            else if (continue_) {
                continue_ = true;
                continue;
            }

            increment_->Evaluate();
        }
    }

    void ForStatement::Break() {
        body_->Halt();
        break_ = true;
    }

    void ForStatement::Continue() {
        body_->Halt();
        continue_ = true;
    }

}
