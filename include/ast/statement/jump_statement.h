#ifndef JUMP_STATEMENT_H_
#define JUMP_STATEMENT_H_

#include <memory>
#include <vm/context.h>
#include "ast/statement/statement.h"

namespace apus {

    class ForStatement;
    class Expression;

    class BreakStatement : public Statement {
    public:

        BreakStatement() {}
        virtual ~BreakStatement() {}

        virtual void Execute(Context& context) override;

    };

    class ContinueStatement : public Statement {
    public:

        ContinueStatement() {}
        virtual ~ContinueStatement() {}

        virtual void Execute(Context& context) override;

    };

    class ReturnStatement : public Statement {
    public:
        ReturnStatement();
        ReturnStatement(std::shared_ptr<Expression> expression);
        ReturnStatement(Expression* expression);

        virtual ~ReturnStatement() {}

        virtual void Execute(Context& context) override;

    private:

        std::shared_ptr<Expression> expression_;

    };

    class ExitStatement : public Statement {
    public:
        ExitStatement() {}
        virtual ~ExitStatement() {}

        virtual void Execute(Context& context) override;

    private:

    };

}

#endif
