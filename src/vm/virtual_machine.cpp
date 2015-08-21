#include "vm/virtual_machine.h"
#include "vm/context.h"

namespace apus {

    VirtualMachine::VirtualMachine() {

    }

    VirtualMachine::~VirtualMachine() {

    }

    StmtListPtr VirtualMachine::getStmtList() {
        return stmt_list_;
    }

    void VirtualMachine::setStmtList(StmtListPtr stmt_list) {
        stmt_list_ = stmt_list;
    }

    void VirtualMachine::Run() {
    }

}
