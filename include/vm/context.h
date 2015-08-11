#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>

namespace apus {

    class DataType;
    class DataTypeTable;

    class FunctionData;
    class FunctionTable;

    class Variable;
    class VariableTable;

    class Context {
    public:

        Context(std::shared_ptr<DataTypeTable> data_type_table);
        virtual ~Context();

        std::shared_ptr<DataType> FindDataType(std::string& name);
        std::shared_ptr<FunctionData> FindFunctionData(std::string& name);
        std::shared_ptr<Variable> FindVariable(std::string& name);

    private:

        std::shared_ptr<DataTypeTable> data_type_table_;
        std::shared_ptr<FunctionTable> function_table_;
        std::shared_ptr<VariableTable> variable_table_;

    };

}

#endif
