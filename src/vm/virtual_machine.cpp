#include "vm/virtual_machine.h"
#include "vm/context.h"

namespace apus {

    VirtualMachine::VirtualMachine() {

    }

    VirtualMachine::~VirtualMachine() {

    }

    StmtPtrList VirtualMachine::getStmtList() {
        return stmt_list_;
    }

    void VirtualMachine::setStmtList(StmtPtrList stmt_list) {
        stmt_list_ = stmt_list;
    }

    DataTypeTablePtr VirtualMachine::getDataTypeTable() {
        return data_type_table_;
    }

    void VirtualMachine::setDataTypeTable(DataTypeTablePtr data_type_table) {
        data_type_table_ = data_type_table;
    }

    void VirtualMachine::Run() {
        static int count = 0;
        Context context;
        std::cout << "vm is Running..." << std::endl;
        
        for(std::shared_ptr<Statement> stmt : stmt_list_) {
            stmt->Execute(context);
            std::cout << "Run count: " << ++count << std::endl;
        }
    }
}
