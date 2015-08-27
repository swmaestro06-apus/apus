#include "vm/context.h"

#include "ast/value/value.h"
#include "vm/data_type_table.h"
#include "vm/variable_table.h"
#include "vm/function_table.h"

#include "utils/BinaryReader.h"

namespace apus {

    Context::Context(shared_ptr<DataTypeTable> data_type_table, std::string binary_file_path)
        : parent_(nullptr), data_type_table_(data_type_table) {

        if (binary_file_path.empty() == false) {
            binary_reader_ = std::make_shared<BinaryReader>(binary_file_path);
        }

        break_ = std::make_shared<bool>(false);
        continue_ = std::make_shared<bool>(false);
        return_ = std::make_shared<bool>(false);

        variable_table_ = make_shared<VariableTable>();
        function_table_ = make_shared<FunctionTable>();
    }

    Context::Context(Context* context) {
        parent_ = context;
        
        break_ = parent_->break_;
        continue_ = parent_->continue_;
        return_ = parent_->return_;

        data_type_table_ = parent_->data_type_table_;
        binary_reader_ = context->binary_reader_;

        variable_table_ = make_shared<VariableTable>();
        function_table_ = make_shared<FunctionTable>();
    }

    Context::~Context() {
    }

    Context Context::BlockBegin() {
        
        Context child(this);

        for (VariablePtr varPtr : param_list_) {
            child.InsertVariable(varPtr);
        }

        param_list_.clear();

        return child;
    }

    std::shared_ptr<Value> Context::BlockEnd() {

        param_list_.clear();

        if (return_value_) {
            parent_->return_value_ = return_value_;
            return parent_->return_value_;
        }

        return nullptr;
    }

    shared_ptr<DataType> Context::FindDataType(string name) {
        return data_type_table_->Find(name);
    }

    shared_ptr<Variable> Context::FindVariable(string name) {

        shared_ptr<Variable> var = nullptr;

        Context* ctx_ptr = this;

        while (ctx_ptr) {

            if ( (var = ctx_ptr->variable_table_->Find(name)) ) {
                return var;
            }

            ctx_ptr = ctx_ptr->parent_;
        }

        return nullptr;
    }

    shared_ptr<Function> Context::FindFunction(string name) {

        shared_ptr<Function> func = nullptr;

        Context* ctx_ptr = this;

        while (ctx_ptr) {

            if ( (func = ctx_ptr->function_table_->Find(name)) ) {
                return func;
            }

            ctx_ptr = ctx_ptr->parent_;
        }
        return nullptr;
    }

    void Context::InsertVariable(shared_ptr<Variable> variable) {
        variable_table_->Insert(variable->getName(), variable);
    }

    void Context::InsertFunction(shared_ptr<Function> function) {
        function_table_->Insert(function->getName(), function);
    }

}

