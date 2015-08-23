#ifndef EXPRESSION_STATEMENT_H_
#define EXPRESSION_STATEMENT_H_

#include <memory>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Context;

    typedef std::shared_ptr<Expression> ExprPtr;

    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement(ExprPtr expression);
        ExpressionStatement(Expression* expression);
        virtual ~ExpressionStatement();

        virtual Type getType() override { return STMT_EXPR; }
        virtual void Execute(Context& context) override;

    private:

        ExprPtr expression_;

    };

}

#endif
