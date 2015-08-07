#include "ast/statement/block.h"
#include "vm/context.h"

namespace apus {

    Block::Block() {

    }

    Block::~Block() {

    }

    void Block::Execute(Context& context) {
        for (std::shared_ptr<Statement> stmt : statements_) {
            stmt->Execute(context);

            if (halt_) {
                halt_ = true;
                break;
            }
        }
    }

    void Block::Halt() {
        halt_ = true;
    }

}
