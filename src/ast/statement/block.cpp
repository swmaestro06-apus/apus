#include "ast/statement/block.h"
#include "vm/context.h"

#include <iostream>

using namespace std;

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

        int count = 0;

        cout << "[Block] is Running.... #stmt is "<< statements_.size() << endl;

        for (std::shared_ptr<Statement> stmt : statements_) {
            stmt->Execute(context);

            cout << "[Block] run count : " << ++count << endl;

            if (context.GetBreak() || context.GetContinue()
                || context.GetReturn() || context.GetExit()) {

                cout << "[Block] ABORT!" << endl;
                break;
            }
        }

        cout <<"[Block] Exiting......" <<endl;    
    }

}
