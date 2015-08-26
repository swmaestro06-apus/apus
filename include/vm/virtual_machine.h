#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "vm/context.h"
#include "ast/statement/statement.h"
#include "vm/data_type_table.h"
#include <memory>
#include <list>

namespace apus {

    class DataType;
    class DataTypeTable;
    class Statement;

    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::shared_ptr<DataTypeTable> DataTypeTablePtr;
    typedef std::shared_ptr<Statement> StmtPtr;
    typedef std::list<StmtPtr> StmtPtrList;

    class VirtualMachine {
    public:
        VirtualMachine();
        virtual ~VirtualMachine();

        StmtPtrList getStmtList();
        void setStmtList(StmtPtrList stmt_list);

        DataTypeTablePtr getDataTypeTable();
        void setDataTypeTable(DataTypeTablePtr data_type_table);

        void Run(std::string binary_file_path);

    private:
        StmtPtrList stmt_list_;
        std::shared_ptr<DataTypeTable> data_type_table_;
    };

}

#endif
