#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "vm/context.h"
#include "ast/statement/statement.h"
#include <memory>
#include <list>

namespace apus {

    typedef std::list<std::shared_ptr<Statement>> StmtListPtr;

    class VirtualMachine {
    public:

        VirtualMachine();
        virtual ~VirtualMachine();

        StmtListPtr getStmtList();
        void setStmtList(StmtListPtr stmt_list);

        void Run();

    private:

        std::list<std::shared_ptr<Statement>> stmt_list_;

    };

}

#endif
