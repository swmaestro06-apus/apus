#ifndef BLOCK_H_
#define BLOCK_H_

#include <memory>
#include <list>
#include "ast/statement/statement.h"

namespace apus {

    class Block : public Statement {
    public:
        Block(std::list<StmtPtr> statements);
        Block(StmtPtr statement);
        virtual ~Block();

        virtual Type getType() override { return STMT_BLOCK; }
        virtual void Execute(Context& context) override;

    private:

        std::list<StmtPtr> statements_;

    };

}

#endif
