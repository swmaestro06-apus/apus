#ifndef PARSER_CONTEXT_H_
#define PARSER_CONTEXT_H_

#include <list>
#include <memory>
#include "common/common.h"
#include "vm/virtual_machine.h"
#include "vm/data_type_table.h"
#include "vm/context.h"

namespace apus {

    class DataType;
    class Statement;
    class VirtualMachine;

    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::shared_ptr<Statement> StmtPtr;

    class ParserContext {
    public:
        ParserContext();
        ParserContext(std::shared_ptr<VirtualMachine> vm);
        ~ParserContext();

        std::shared_ptr<VirtualMachine> getVM();
        void setVM(std::shared_ptr<VirtualMachine> vm);

        // send data type table to virtual machine
        void SendDataTypeTableToVM();

        // get/set method for name of current data type
        void setCurrentName(const std::string& name);
        std::string getCurrentName();

        // get/set method for shared ptr of current data type
        void setCurrentDataType(DataTypePtr type);
        DataTypePtr getCurrentDataType();

        // Add a data type into current data type(struct or union)
        void AddToCurrentDataType(const std::string& name,
                const std::string& type_name);
        void AddToCurrentDataType(const std::string& name, TypeSpecifier type);
        void AddToCurrentDataType(const std::string& name, DataTypePtr type);
        void AddToCurrentDataType(const std::string& name, DataType* type);

        void ChangeCurrentDataType();

    private:
        std::shared_ptr<VirtualMachine> vm_;    // virtual machine
        // data type table
        std::shared_ptr<DataTypeTable> data_type_table_;
        DataTypePtr current_data_type_;          // current data type
        std::string current_name_;               // name of current data type
    };
}

#endif

