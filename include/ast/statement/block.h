#ifndef BLOCK_H_
#define BLOCK_H_

#include <memory>
#include <list>
#include "ast/statement/statement.h"

namespace apus {

    class Block : public Statement {
    public:
        Block();
        virtual ~Block();

        virtual void Execute(Context& context) override;

        void Halt();

    private:

        std::list<std::shared_ptr<Statement>> statements_;
        bool halt_;

    };
}

#endif
