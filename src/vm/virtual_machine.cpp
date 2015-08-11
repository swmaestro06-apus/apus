#include "vm/virtual_machine.h"
#include "vm/context.h"
#include "ast/statement/statement.h"

namespace apus {

    VirtualMachine::VirtualMachine()
        : context_(nullptr) {

    }

    VirtualMachine::~VirtualMachine() {
    }

    void VirtualMachine::Run(
            std::shared_ptr<DataTypeTable> data_type_table,
            std::vector<std::shared_ptr<apus::Statement>> instructions) {

        context_ = std::make_shared<Context>(data_type_table);

        for (std::shared_ptr<apus::Statement> stmt : instructions) {
            stmt->Execute(*context_);
        }
    }

}
