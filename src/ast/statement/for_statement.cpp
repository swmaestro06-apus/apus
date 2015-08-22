#include "ast/statement/for_statement.h"
#include "ast/statement/block.h"
#include "ast/value/value.h"
#include "vm/context.h"

#include <iostream>
using namespace std;

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

        cout << "[FOR] begin " <<endl;

        if (initialization_) {
            initialization_->Evaluate(context);
        }

        cout << "[FOR] initialised " << endl;

        while (true) {

            if (termination_) {

                if (Value::IsTrue(termination_->Evaluate(context))) {
                    
                    cout << "[FOR] looping.. body begin" << endl;
                    
                    if (body_) {
                        body_->Execute(context);
                    }

                    cout << "[FOR] body end" << endl;

                    if (context.GetBreak()) {
                        context.SetBreak(false);
                        cout << "[FOR] loop breaking" << endl;
                        break;
                    }

                    if (context.GetContinue()) {
                        context.SetContinue(false);
                        cout << "[FOR] loop continueing" << endl;
                    }

                    cout << "[FOR] increment evaluating" <<endl;
                    if (increment_) {
                        increment_->Evaluate(context);
                    }

                    cout << "[FOR] end of loop " <<endl;
                }
                else {
                    cout << "[FOR] TERMINATING loop" <<endl;
                    break;
                }
            }

        }

        cout << "[FOR] end " << endl;
    }

}
