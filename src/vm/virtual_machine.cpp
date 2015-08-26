#include "vm/virtual_machine.h"
#include "vm/context.h"
#include "vm/function_table.h"

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

        Context context(data_type_table_);
        // Insert Built-in function
        context.InsertFunction(std::make_shared<PrintS64>(context));
        context.InsertFunction(std::make_shared<PrintSTR8>(context));

        std::cout << "vm is Running..." << std::endl;
        
        for(std::shared_ptr<Statement> stmt : stmt_list_) {
            stmt->Execute(context);
            std::cout << "Run count: " << ++count << std::endl;
        }
    }
}
