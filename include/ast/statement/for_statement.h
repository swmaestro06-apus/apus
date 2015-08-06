#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H

#include <memory>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Block;

    class ForStatement : public Statement {
    public:

        ForStatement();
        virtual ~ForStatement();

        virtual void Execute() override;

        void Break();
        void Continue();

    private:

        std::shared_ptr<Expression> initialization_;
        std::shared_ptr<Expression> termination_;
        std::shared_ptr<Expression> increment_;

        std::shared_ptr<Block>      body_;

        bool break_;
        bool continue_;
    };
}

#endif
