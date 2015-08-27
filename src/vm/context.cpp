#include "vm/context.h"

#include "ast/value/value.h"
#include "vm/data_type_table.h"
#include "vm/variable_table.h"

namespace apus {

    Context::Context(shared_ptr<DataTypeTable> data_type_table)
        : parent_(nullptr), data_type_table_(data_type_table) {

        break_ = std::make_shared<bool>(false);
        continue_ = std::make_shared<bool>(false);
        return_ = std::make_shared<bool>(false);

        variable_table_ = make_shared<VariableTable>();
        // TODO : create function table
    }

    Context::Context(Context* context) {
        parent_ = context;

        break_ = parent_->break_;
        continue_ = parent_->continue_;
        return_ = parent_->return_;

        data_type_table_ = parent_->data_type_table_;

        variable_table_ = make_shared<VariableTable>();
        // TODO : create function table
    }

    Context::~Context() {
    }

    Context Context::BlockBegin() {

        Context child(*this);
        // TODO : Insert params into child.variable_table_

        return child;
    }

    std::shared_ptr<Value> Context::BlockEnd() {

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

        shared_ptr<VariableTable> var_tab = variable_table_;
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

    void Context::InsertVariable(shared_ptr<Variable> variable) {
        variable_table_->Insert(variable->getName(), variable);
    }

}

