#include "ast/statement/block.h"
#include "vm/context.h"

namespace apus {

    Block::Block(std::list<StmtPtr> statements)
        : statements_(statements) {
    }

    Block::Block(StmtPtr statement) {
        statements_.push_back(statement);
    }

    Block::~Block() {

    }

    void Block::Execute(Context& context) {

        for (StmtPtr stmt : statements_) {
            stmt->Execute(context);

            if (context.GetBreak() || context.GetContinue()
                || context.GetReturn() || context.GetExit()) {
                break;
            }
        }
    }

}
