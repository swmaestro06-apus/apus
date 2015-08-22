#include "ast/statement/if_statement.h"
#include "ast/statement/block.h"
#include "ast/expression.h"

#include "ast/value/value.h"

#include "vm/context.h"

#include <iostream>
using namespace std;

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

        cout << "[IF] end " <<endl;
    }

}
