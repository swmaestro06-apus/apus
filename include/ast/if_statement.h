#ifndef IF_STATEMENT_H_
#define IF_STATEMENT_H_
#include <memory>
#include "statement.h"

namespace apus {

    class Block;
    class Expression;

    class IfStatement : public Statement {
    public:
        IfStatement();
        virtual ~IfStatement();

        virtual void Execute() override;

    private:
        std::shared_ptr<Expression> condition_;

        std::shared_ptr<Block> true_block_;
        std::shared_ptr<Block> false_block_;
    };

}

#endif