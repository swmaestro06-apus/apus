#include "vm/function_table.h"
#include "vm/variable_table.h"

#include "ast/value/signed_int_value.h"

#include <iostream>

namespace apus {

    // Function class

    Function::Function() {
    }

    Function::Function(const std::string& name) {
        name_ = name;
        return_type_ = nullptr;
    }

    Function::Function(const std::string& name, DataTypePtr return_type) {
        name_ = name;
        return_type_ = return_type;
    }

    Function::Function(const std::string& name, DataTypePtr return_type, list<VariablePtr> arg_list) {
        name_ = name;
        return_type_ = return_type;
        arg_list_ = arg_list;
    }

    Function::~Function() {
    }

    // FunctionTable class

    FunctionTable::FunctionTable() {

    }

    void FunctionTable::Insert(std::string name,
                               std::shared_ptr<Function> function) {
        map_[name] = function;
    }

    std::shared_ptr<Function> FunctionTable::Find(std::string& name) {
        FunctionMap::iterator it = map_.find(name);

        if(it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}
