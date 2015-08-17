#include "ast/statement/block.h"
#include "vm/context.h"

namespace apus {

    Block::Block(std::list<std::shared_ptr<Statement>> statements)
        : statements_(statements) {
    }

    Block::Block(std::shared_ptr<Statement> statement) {
        statements_.push_back(statement);
    }

    Block::~Block() {

    }

    void Block::Execute(Context& context) {

        for (std::shared_ptr<Statement> stmt : statements_) {
            stmt->Execute(context);

            if (context.GetBreak() || context.GetContinue()
                || context.GetReturn() || context.GetExit()) {
                break;
            }
        }
    }

}
