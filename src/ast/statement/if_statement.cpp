#include "ast/statement/if_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"
#include "vm/context.h"

namespace apus {

    IfStatement::IfStatement(ExprPtr condition,
                             StmtPtr true_block,
                             StmtPtr false_block)
        : condition_(condition), true_block_(true_block),
          false_block_(false_block) {
    }

    IfStatement::IfStatement(Expression *condition,
                             Statement *true_block,
                             Statement *false_block) {
        condition_ = ExprPtr(condition);
        true_block_ = StmtPtr(true_block);
        false_block_ = StmtPtr(false_block);
    }

    IfStatement::~IfStatement() { 

    }

    void IfStatement::Execute(Context& context) {
        if( condition_->Evaluate(context) ) {
            true_block_->Execute(context);
        }
        else {
            false_block_->Execute(context);
        }
    }

}
