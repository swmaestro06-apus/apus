#ifndef VARIABLE_TABLE_H_
#define VARIABLE_TABLE_H_

#include <memory>
#include <string>
#include <map>
#include <list>
#include <cstdarg>
#include "ast/value/value.h"
#include "vm/data_type_table.h"

namespace apus {

    class Value;
    class DataType;
    class Variable;
    
    typedef std::shared_ptr<Value> ValuePtr;
    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::shared_ptr<Variable> VarPtr;
    typedef std::map< std::string, VarPtr > VariableMap;

    class Variable {
    public:
        Variable();
        Variable(const std::string& name);
        Variable(const std::string& name, DataTypePtr type);
        ~Variable();

        inline std::string GetName();
        inline void SetName(const std::string& name);

        inline DataTypePtr GetType();
        inline void SetType(DataTypePtr type);
        void SetType(DataType* type);

    protected:
        std::string name_;                  // name of variable
        DataTypePtr type_;                  // data type
    };

    class NonArrVariable : public Variable {
    public:
        NonArrVariable();
        NonArrVariable(const std::string& name);
        NonArrVariable(const std::string& name, DataTypePtr type);
        NonArrVariable(const std::string& name, DataTypePtr type, ValuePtr value);
        ~NonArrVariable();

        inline ValuePtr GetValue();
        void SetValue(ValuePtr value);
        void SetValue(Value* value);

    private:
        ValuePtr value_;                    // value
    };

    class ArrayVariable : public Variable {
    public:
        ArrayVariable();
        ArrayVariable(const std::string& name);
        ~ArrayVariable();

        ValuePtr GetValue(int num, ... );
        void AddValue(ValuePtr value);
        void AddValue(Value* value);

    private:
        std::list<ValuePtr> value_list_;    // value list
        
        int array_size_;                    // product of dimension sizes
        std::list<int> dimension_list_;     // size of each dimension
    };

    class VariableTable {
    public:
        VariableTable();
        VariableTable(std::shared_ptr<VariableTable> parent);
        ~VariableTable();

        void Insert(std::string name, std::shared_ptr<Variable> variable);
        std::shared_ptr<Variable> Find(std::string& name);

        inline std::shared_ptr<VariableTable> GetParent() { return parent_; }

    private:
        VariableMap map_;
        std::shared_ptr<VariableTable> parent_;
    };
}

#endif
