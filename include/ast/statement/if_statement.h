#ifndef IF_STATEMENT_H_
#define IF_STATEMENT_H_

#include <memory>
#include "ast/statement/statement.h"

namespace apus {

    class Expression;
    class Block;

    typedef std::shared_ptr<Expression> ExprPtr;

    class IfStatement : public Statement {
    public:
        IfStatement(ExprPtr condition,
                    StmtPtr true_block,
                    StmtPtr false_block);

        IfStatement(Expression* condition,
                    Statement* true_block,
                    Statement* false_block);

        virtual ~IfStatement();

        virtual Type getType() override { return STMT_IF; }
        virtual void Execute(Context& context) override;

    private:
        ExprPtr condition_;

        StmtPtr true_block_;
        StmtPtr false_block_;
    };

}

#endif
