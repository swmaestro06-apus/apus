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

            if (context.GetBreak()) {
                context.SetBreak(false);
                break;
            }

            if (context.GetContinue()) {
                context.SetContinue(false);
            }

            increment_->Evaluate(context);
        }
    }

}
