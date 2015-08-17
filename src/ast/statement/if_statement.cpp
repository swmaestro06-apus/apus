#include "ast/statement/if_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"
#include "vm/context.h"

namespace apus {

    IfStatement::IfStatement(std::shared_ptr<Expression> condition,
                             std::shared_ptr<Block> true_block,
                             std::shared_ptr<Statement> false_block)
        : condition_(condition), true_block_(true_block),
          false_block_(false_block) {
    }

    IfStatement::IfStatement(Expression *condition,
                             Block *true_block,
                             Statement *false_block) {
        condition_ = std::shared_ptr<Expression>(condition);
        true_block_ = std::shared_ptr<Block>(true_block);
        false_block_ = std::shared_ptr<Statement>(false_block);
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
