#ifndef JUMP_STATEMENT_H_
#define JUMP_STATEMENT_H_

#include <memory>
#include "ast/statement/statement.h"

namespace apus {

    class ForStatement;
    class Expression;

    class BreakStatement : public Statement {
    public:

        BreakStatement(std::shared_ptr<ForStatement> loop_statement);
        BreakStatement(ForStatement* loop_statement);

        virtual ~BreakStatement();

        virtual void Execute() override;

    private:

        std::shared_ptr<ForStatement> loop_statement_;

    };

    class ContinueStatement : public Statement {
    public:

        ContinueStatement(std::shared_ptr<ForStatement> loop_statement);
        ContinueStatement(ForStatement* loop_statement);

        virtual ~ContinueStatement();

        virtual void Execute() override;

    private:

        std::shared_ptr<ForStatement> loop_statement_;

    };

    class ReturnStatement : public Statement {
    public:
        ReturnStatement();
        ReturnStatement(std::shared_ptr<Expression> expression);
        ReturnStatement(Expression* expression);

        virtual ~ReturnStatement();

    private:

        std::shared_ptr<Expression> expression_;

    };

}

#endif
