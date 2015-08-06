#include "ast/statement/block.h"

namespace apus {

    Block::Block() {

    }

    Block::~Block() {

    }

    void Block::Execute() {
        for (std::shared_ptr<Statement> stmt : statements_) {
            stmt->Execute();

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