#include "vm/virtual_machine.h"
#include "vm/context.h"

namespace apus {

    VirtualMachine::VirtualMachine() {
        context_ = new Context();
    }

    VirtualMachine::~VirtualMachine() {
        delete context_;
    }

    void VirtualMachine::Run() {
    }

}
