#include "vm/variable_table.h"

namespace apus {

    // Variable class

    Variable::Variable(const std::string& name, DataTypePtr type) {
        name_ = name;
        data_type_ = type;

        CreateChildVariables();
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

    VarPtr Variable::getChildVariable(const std::string& name) {
        VariableMap::iterator it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void Variable::InsertChildVariable(const std::string& name, VarPtr var) {
        map_[name] = var;
    }

    bool Variable::IsStructVariable() {
        if (map_.size() != 0) {
            return true;
        } else {
            return false;
        }
    }

    void Variable::CreateChildVariables() {
        if (data_type_ != NULL && data_type_->GetType() == STRUCT) {
            // key = string, value = shared pointer to DataType
            DataTypeMap map = data_type_->GetMap();
            for (DataTypeMap::iterator it = map.begin();
                it != map.end(); it++) {
                VarPtr var = std::make_shared<Variable>(it->first, it->second);
                map_[it->first] = var;
            }
        }
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
