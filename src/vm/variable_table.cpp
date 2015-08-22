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
        type_ = type;
    }

    Variable::Variable(const std::string& name, DataTypePtr type, 
        ValuePtr value) {
        name_ = name;
        type_ = type;
        value_ = value;
    }

    Variable::~Variable() {
    }

    inline std::string Variable::GetName() {
        return name_;
    }

    void Variable::SetName(const std::string& name) {
        name_ = name;
    }

    inline DataTypePtr Variable::GetType() {
        return type_;
    }

    void Variable::SetType(DataTypePtr type) {
        type_ = type;
    }

    void Variable::SetType(DataType* type) {
        DataTypePtr type_ptr = std::make_shared<DataType>(*type);
        type_ = type_ptr;
    }

    inline ValuePtr Variable::GetValue() {
        return value_;
    }

    void Variable::SetValue(ValuePtr value) {
        value_ = value->Copy();
    }

    void Variable::SetValue(Value* value) {
        value_ = value->Copy();
    }

    // ArrayVariable class

    ArrayVariable::ArrayVariable() {
    }

    ArrayVariable::ArrayVariable(const std::string& name) {
        name_ = name;
    }

    ArrayVariable::~ArrayVariable() {
    }

    inline std::string ArrayVariable::GetName() {
        return name_;
    }

    void ArrayVariable::SetName(const std::string& name) {
        name_ = name;
    }

    inline DataTypePtr ArrayVariable::GetElementType() {
        return element_type_;
    }

    void ArrayVariable::SetElementType(DataTypePtr type) {
        element_type_ = type;
    }

    void ArrayVariable::SetElementType(DataType* type) {
        DataTypePtr type_ptr = std::make_shared<DataType>(*type);
        element_type_ = type_ptr;
    }

    ValuePtr ArrayVariable::GetValue(int num, ... ) {
        int array_index = 1;

        va_list args;
        va_start(args, num);
        for (int i = 0; i < num; i++) {
            array_index *= (va_arg(args, int) + 1);
        }
        va_end(args);
        array_index--;

        if (array_index < value_list_.size()) {
            std::list<ValuePtr>::iterator it = value_list_.begin();
            std::advance(it, array_index);
            return *it;
        } else {
            return nullptr;
        }
    }

    void ArrayVariable::AddValue(ValuePtr value) {
        value_list_.push_back(value->Copy());
    }

    void ArrayVariable::AddValue(Value* value) {
        value_list_.push_back(value->Copy());
    }

    // VariableTable class

    VariableTable::VariableTable(std::shared_ptr<VariableTable> parent)
        : parent_(parent) {

    }

    void VariableTable::Insert(std::string name,
                               std::shared_ptr<Variable> variable) {
        map_[name] = variable;
    }

    std::shared_ptr<Variable> VariableTable::Find(std::string& name) {
        VariableMap::iterator it = map_.find(name);

        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}
