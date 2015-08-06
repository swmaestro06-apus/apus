#include "vm/virtual_machine.h"
#include "ast/statement/statement.h"

namespace apus {

    VirtualMachine::VirtualMachine() {

    }

    VirtualMachine::~VirtualMachine() {

    }

    void VirtualMachine::Run(std::vector<std::shared_ptr<apus::Statement>> instructions) {
        for (std::shared_ptr<apus::Statement> stmt : instructions) {
            stmt->Execute();
        }
    }

}
