#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H

#include <memory>
#include <ast/expression.h>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Block;

    typedef std::shared_ptr<Expression> ExprPtr;

    class ForStatement : public Statement {
    public:

        ForStatement (ExprPtr initialization,
                      ExprPtr termination,
                      ExprPtr increment,
                      StmtPtr body_statement);

        ForStatement (Expression* initialization,
                      Expression* termination,
                      Expression* increment,
                      Statement* body);

        virtual ~ForStatement ();

        virtual Type getType() override { return STMT_FOR; }
        virtual void Execute(Context& context) override;

    private:

        ExprPtr initialization_;
        ExprPtr termination_;
        ExprPtr increment_;

        StmtPtr  body_;
    };
}

#endif
