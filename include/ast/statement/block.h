#ifndef BLOCK_H_
#define BLOCK_H_

#include <memory>
#include <list>
#include "ast/statement/statement.h"

namespace apus {

    class Block : public Statement {
    public:
        Block(std::list<std::shared_ptr<Statement>> statements);
        Block(std::shared_ptr<Statement> statement);
        virtual ~Block();

        virtual Type getType() override { return STMT_BLOCK; }
        virtual void Execute(Context& context) override;

    private:

        std::list<std::shared_ptr<Statement>> statements_;

    };

}

#endif
