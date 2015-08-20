#include "vm/virtual_machine.h"
#include "vm/context.h"

#include <iostream>

using namespace std;

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

        static int count = 0;

        Context context;

        cout << "vm is Running...." << endl;
        
        for(std::shared_ptr<Statement> stmt : stmt_list_) {

            stmt->Execute(context);
            
            cout << "RUN count : " << ++count << endl;
        }        
        
    }

}
