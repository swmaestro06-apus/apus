#include "vm/virtual_machine.h"
#include "vm/context.h"
#include "vm/function_table.h"

#include "vm/builtin_functions.h"

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

    void VirtualMachine::Run(std::string binary_file_path) {
        
        Context context(data_type_table_, binary_file_path);

        // Insert Built-in function
        context.InsertFunction(std::make_shared<PrintS64>(context));
        context.InsertFunction(std::make_shared<PrintSTR8>(context));

        context.InsertFunction(std::make_shared<ReadS8>(context));
        context.InsertFunction(std::make_shared<ReadS16>(context));
        context.InsertFunction(std::make_shared<ReadS32>(context));
        context.InsertFunction(std::make_shared<ReadS64>(context));

        context.InsertFunction(std::make_shared<ReadU8>(context));
        context.InsertFunction(std::make_shared<ReadU16>(context));
        context.InsertFunction(std::make_shared<ReadU32>(context));
        context.InsertFunction(std::make_shared<ReadU64>(context));

        context.InsertFunction(std::make_shared<ReadC8>(context));
        context.InsertFunction(std::make_shared<ReadC16>(context));
        context.InsertFunction(std::make_shared<ReadC32>(context));
        
        for(std::shared_ptr<Statement> stmt : stmt_list_) {
            stmt->Execute(context);
        }
    }
}
