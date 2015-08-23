#include "ast/statement/block.h"
#include "vm/context.h"

#include <iostream>

using namespace std;

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

        Context child = context.BlockBegin();

        int count = 0;

        for (StmtPtr stmt : statements_) {

            stmt->Execute(child);

            if (context.GetBreak() || context.GetContinue()
                || context.GetReturn() || context.GetExit()) {
                break;
            }
        }

        child.BlockEnd();
    }

}
