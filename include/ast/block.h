#ifndef BLOCK_H_
#define BLOCK_H_

#include "statement.h"

namespace apus {

    class Block : public Statement {
    public:
        Block();
        virtual ~Block();

        virtual void Execute() override;

    private:

    };
}

#endif