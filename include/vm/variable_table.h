#ifndef VARIABLE_TABLE_H_
#define VARIABLE_TABLE_H_

#include <memory>
#include <string>
#include <map>

namespace apus {

    class Value;
    class DataType;

    class Variable {
    public:

        Variable(std::string name, std::shared_ptr<DataType> type,
                 std::shared_ptr<Value> value)
            : name_(name), type_(type), value_(value) { }

        inline std::string GetName() { return name_; }
        inline std::shared_ptr<DataType> GetType() { return type_; }
        inline std::shared_ptr<Value> GetValue() { return value_; }

    private:
        std::string name_;
        std::shared_ptr<DataType> type_;
        std::shared_ptr<Value> value_;
    };

    class VariableTable {
    public:
        typedef std::map<std::string, std::shared_ptr<Variable>> VariableMap;

        VariableTable(std::shared_ptr<VariableTable> parent);

        void Insert(std::string name, std::shared_ptr<Variable> variable);
        std::shared_ptr<Variable> Find(std::string& name);

        inline std::shared_ptr<VariableTable> GetParent() { return parent_; }

    private:

        VariableMap map_;
        std::shared_ptr<VariableTable> parent_;
    };
}

#endif
