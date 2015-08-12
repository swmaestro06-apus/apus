#include "ast/statement/for_statement.h"
#include "ast/statement/block.h"
#include "vm/context.h"

namespace apus {

    ForStatement::ForStatement(std::shared_ptr<Expression> initialization,
                               std::shared_ptr<Expression> termination,
                               std::shared_ptr<Expression> increment,
                               std::shared_ptr<Block> body)

        : initialization_(initialization), termination_(termination),
          increment_(increment), body_(body) {

    }

    ForStatement::~ForStatement() {

    }

    void ForStatement::Execute(Context& context) {
        initialization_->Evaluate(context);

        while (termination_->Evaluate(context)) {
            body_->Execute(context);

            if (break_) {
                break_ = true;
                break;
            }
            else if (continue_) {
                continue_ = true;
                continue;
            }

            increment_->Evaluate(context);
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
