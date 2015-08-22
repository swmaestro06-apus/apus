#include "ast/statement/expression_statement.h"
#include "ast/expression.h"

#include "vm/context.h"

#include <iostream>
using namespace std;

namespace apus {

    ExpressionStatement::ExpressionStatement(
            ExprPtr expression)
            : expression_(expression) {

    }

    ExpressionStatement::ExpressionStatement(Expression* expression) {
        ExpressionStatement(ExprPtr(expression));
    }

    ExpressionStatement::~ExpressionStatement() {

    }

    void ExpressionStatement::Execute(Context& context) {

        cout << "[expr_stmt] executing..." << endl;
        if (expression_) {
            cout << "[expr_stmt] evaluating....." << endl;

            auto ret = expression_->Evaluate(context);
            if (ret == nullptr)
                cout << "[expr_stmt] Evaluation was wroing" <<endl;
        }
    }
}
