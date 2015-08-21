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

        virtual Type getType() override { return STMT_BREAK; }
        virtual void Execute(Context& context) override;

    };

    class ContinueStatement : public Statement {
    public:

        ContinueStatement() {}
        virtual ~ContinueStatement() {}

        virtual Type getType() override { return STMT_CONTINUE; }
        virtual void Execute(Context& context) override;

    };

    class ReturnStatement : public Statement {
    public:
        ReturnStatement();
        ReturnStatement(std::shared_ptr<Expression> expression);
        ReturnStatement(Expression* expression);

        virtual ~ReturnStatement() {}

        virtual Type getType() override { return STMT_RETURN; }
        virtual void Execute(Context& context) override;

    private:

        std::shared_ptr<Expression> expression_;

    };

    class ExitStatement : public Statement {
    public:
        ExitStatement() {}
        ExitStatement(std::shared_ptr<Expression> expression);
        ExitStatement(Expression* expression);
        virtual ~ExitStatement() {}

        virtual Type getType() override { return STMT_EXIT; }
        virtual void Execute(Context& context) override;

    private:

        std::shared_ptr<Expression> expression_;

    };

}

#endif
