#include <cstdlib>

#include "ast/statement/jump_statement.h"
#include "ast/statement/for_statement.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/unsigned_int_value.h"

#include "vm/context.h"

namespace apus {

    void BreakStatement::Execute(Context& context) {
        context.SetBreak(true);
    }

    void ContinueStatement::Execute(Context& context) {
        context.SetContinue(true);
    }

    ReturnStatement::ReturnStatement()
        : expression_(nullptr) {

    }

    ReturnStatement::ReturnStatement(ExprPtr expression)
        : expression_(expression) {

    }

    ReturnStatement::ReturnStatement(Expression *expression)
        : ReturnStatement( ExprPtr(expression) ) {
    }

    void ReturnStatement::Execute(Context& context) {

        if (expression_) {
            expression_->Evaluate(context);
        }

        context.SetReturn(true);
    }

    ExitStatement::ExitStatement(ExprPtr expression)
        : expression_(expression) {

    }

    ExitStatement::ExitStatement(Expression *expression)
        : ExitStatement( ExprPtr(expression) ) {
    }

    void ExitStatement::Execute(Context &context) {

        int int_val = 0;

        if (expression_) {
            ValuePtr val = expression_->Evaluate(context);
            TypeSpecifier val_type = val->getType();

            if (S8 <= val_type && val_type <= S64) {
                int_val = std::dynamic_pointer_cast<SignedIntValue>(val)->getIntValue();
            }
            else if (U8 <= val_type && val_type <= U64) {
                int_val = std::dynamic_pointer_cast<UnsignedIntValue>(val)->getUIntValue();
            }

        }

        exit(int_val);
    }

}
