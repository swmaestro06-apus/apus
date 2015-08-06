#include "ast/statement/if_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"

namespace apus {

    IfStatement::IfStatement() {
    }

    IfStatement::~IfStatement() { 

    }

    void IfStatement::Execute() {
        if( condition_->Evaluate() ) {
            true_block_->Execute();
        }
        else {
            false_block_->Execute();
        }
    }

}