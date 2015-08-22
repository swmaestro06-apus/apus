#include "ast/statement/for_statement.h"
#include "ast/statement/block.h"
#include "ast/value/value.h"
#include "vm/context.h"

namespace apus {

    ForStatement::ForStatement(std::shared_ptr<Expression> initialization,
                               std::shared_ptr<Expression> termination,
                               std::shared_ptr<Expression> increment,
                               std::shared_ptr<Statement> body)

        : initialization_(initialization), termination_(termination),
          increment_(increment), body_(body) {
    }

    ForStatement::ForStatement(Expression* initialization,
                               Expression* termination,
                               Expression* increment,
                               Statement* body)
        : ForStatement(std::shared_ptr<Expression>(initialization),
                       std::shared_ptr<Expression>(termination),
                       std::shared_ptr<Expression>(increment),
                       std::shared_ptr<Statement>(body)) {
    }

    ForStatement::~ForStatement() {

    }

    void ForStatement::Execute(Context& context) {

        if (initialization_) {
            initialization_->Evaluate(context);
        }

        while (true) {

            if (termination_) {

                if (Value::IsTrue(termination_->Evaluate(context))) {

                    if (body_) {
                        body_->Execute(context);
                    }

                    if (context.GetBreak()) {
                        context.SetBreak(false);
                        break;
                    }

                    if (context.GetContinue()) {
                        context.SetContinue(false);
                    }

                    if (increment_) {
                        increment_->Evaluate(context);
                    }
                }
                else {
                    break;
                }
            }

        }
    }

}
