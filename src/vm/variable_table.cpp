#include "vm/variable_table.h"

namespace apus {

    // Variable class

    Variable::Variable() {
    }

    Variable::Variable(const std::string& name) {
        name_ = name;
    }

    Variable::Variable(const std::string& name, DataTypePtr type) {
        name_ = name;
        data_type_ = type;
    }

    Variable::~Variable() {
    }

    TypeSpecifier Variable::getType() {
        return data_type_->GetType();
    }

    std::string Variable::getName() {
        return name_;
    }

    void Variable::setName(const std::string& name) {
        name_ = name;
    }

    DataTypePtr Variable::getDataType() {
        return data_type_;
    }

    void Variable::setDataType(DataTypePtr type) {
        data_type_ = type;
    }

    ValuePtr Variable::getValue() {
        return value_;
    }

    void Variable::setValue(ValuePtr value) {
        value_ = value;
    }

    // VariableTable class

    VariableTable::VariableTable() {
    }

    VariableTable::~VariableTable() {
    }

    void VariableTable::Insert(const std::string name,
                               std::shared_ptr<Variable> variable) {
        map_[name] = variable;
    }

    std::shared_ptr<Variable> VariableTable::Find(const std::string& name) {
        VariableMap::iterator it = map_.find(name);

        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}
