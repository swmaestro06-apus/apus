#include "vm/virtual_machine.h"
#include "vm/context.h"
#include "ast/statement/statement.h"

namespace apus {

    VirtualMachine::VirtualMachine() {
        context_ = new Context();
    }

    VirtualMachine::~VirtualMachine() {
        delete context_;
    }

    void VirtualMachine::Run(std::vector<std::shared_ptr<apus::Statement>> instructions) {
        for (std::shared_ptr<apus::Statement> stmt : instructions) {
            stmt->Execute(*context_);
        }
    }

}
