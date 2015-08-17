#ifndef EXPRESSION_STATEMENT_H_
#define EXPRESSION_STATEMENT_H_

#include <memory>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Context;

    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement(std::shared_ptr<Expression> expression);
        virtual ~ExpressionStatement();

        virtual void Execute(Context& context) override;

    private:

        std::shared_ptr<Expression> expression_;

    };

}

#endif
