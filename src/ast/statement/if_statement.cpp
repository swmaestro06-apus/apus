#include "ast/statement/if_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"

#include "ast/value/value.h"

#include "vm/context.h"

namespace apus {

    IfStatement::IfStatement(std::shared_ptr<Expression> condition,
                             std::shared_ptr<Statement> true_block,
                             std::shared_ptr<Statement> false_block)
        : condition_(condition), true_block_(true_block),
          false_block_(false_block) {
    }

    IfStatement::IfStatement(Expression *condition,
                             Statement *true_block,
                             Statement *false_block) {
        condition_ = std::shared_ptr<Expression>(condition);
        true_block_ = std::shared_ptr<Statement>(true_block);
        false_block_ = std::shared_ptr<Statement>(false_block);
    }

    IfStatement::~IfStatement() { 

    }

    void IfStatement::Execute(Context& context) {

        if (condition_) {

            if (Value::IsTrue(condition_->Evaluate(context))) {

                if (true_block_) {
                    true_block_->Execute(context);
                }
            }

            else {

                if (false_block_) {
                    false_block_->Execute(context);
                }
            }

        }
    }

}
