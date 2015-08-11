#include "vm/context.h"
#include "vm/data_type_table.h"
#include "vm/function_table.h"
#include "vm/variable_table.h"

namespace apus {

    Context::Context(std::shared_ptr<DataTypeTable> data_type_table)
        : data_type_table_(data_type_table) {

        function_table_ = std::make_shared<FunctionTable>(nullptr);
        variable_table_ = std::make_shared<VariableTable>(nullptr);
    }

    Context::~Context() {

    }

    std::shared_ptr<DataType> Context::FindDataType(std::string &name) {
        return data_type_table_->Find(name);
    }

    std::shared_ptr<FunctionData> Context::FindFunctionData(std::string &name) {

        std::shared_ptr<FunctionTable> func_table = function_table_;

        do {

            std::shared_ptr<FunctionData> func_data = nullptr;
            if ( (func_data = func_table->Find(name)) != nullptr) {
                return func_data;
            }

        } while ( (func_table = func_table->GetParent()) != nullptr );

        return nullptr;
    }

    std::shared_ptr<Variable> Context::FindVariable(std::string &name) {

        std::shared_ptr<VariableTable> var_table = variable_table_;

        do {

            std::shared_ptr<Variable> variable = nullptr;
            if ( (variable = var_table->Find(name)) != nullptr) {
                return variable;
            }

        } while ( (var_table = var_table->GetParent()) != nullptr );

        return nullptr;
    }

}
