#include "ast/statement/for_statement.h"
#include "ast/statement/block.h"
#include "ast/value/value.h"
#include "vm/context.h"

#include <iostream>
using namespace std;

namespace apus {

    ForStatement::ForStatement(ExprPtr initialization,
                               ExprPtr termination,
                               ExprPtr increment,
                               StmtPtr body)

        : initialization_(initialization), termination_(termination),
          increment_(increment), body_(body) {
    }

    ForStatement::ForStatement(Expression* initialization,
                               Expression* termination,
                               Expression* increment,
                               Statement* body) {

        initialization_ = ExprPtr(initialization);
        termination_ = ExprPtr(termination);
        increment_ = ExprPtr(increment);
        body_ = StmtPtr(body);
    }

    ForStatement::~ForStatement() {

    }

    void ForStatement::Execute(Context& context) {

        int count = 0;

        cout << "[FOR] begin " <<endl;

        if (initialization_) {
            initialization_->Evaluate(context);
        }

        cout << "[FOR] initialised " << endl;

        while (true) {

            if (termination_) {

                if (Value::IsTrue(termination_->Evaluate(context))) {
                    
                    cout << "[FOR] looping.. body begin, count : " << ++count << endl;
                    
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
