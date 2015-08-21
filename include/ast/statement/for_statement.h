#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H

#include <memory>
#include <ast/expression.h>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Block;

    class ForStatement : public Statement {
    public:

        ForStatement (std::shared_ptr<Expression> initialization,
                      std::shared_ptr<Expression> termination,
                      std::shared_ptr<Expression> increment,
                      std::shared_ptr<Statement> body_statement);

        ForStatement (Expression* initialization,
                      Expression* termination,
                      Expression* increment,
                      Statement* body);

        virtual ~ForStatement ();

        virtual Type getType() override { return STMT_FOR; }
        virtual void Execute(Context& context) override;

    private:

        std::shared_ptr<Expression> initialization_;
        std::shared_ptr<Expression> termination_;
        std::shared_ptr<Expression> increment_;

        std::shared_ptr<Statement>  body_;
    };
}

#endif
