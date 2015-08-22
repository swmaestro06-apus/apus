#ifndef VARIABLE_TABLE_H_
#define VARIABLE_TABLE_H_

#include <memory>
#include <string>
#include <map>
#include <list>
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
        Variable(const std::string& name, DataTypePtr type, ValuePtr value);
        ~Variable();

        inline std::string GetName();
        void SetName(const std::string& name);

        inline DataTypePtr GetType();
        void SetType(DataTypePtr type);
        void SetType(DataType* type);

        inline ValuePtr GetValue();
        void SetValue(ValuePtr value);
        void SetValue(Value* value);

    private:
        std::string name_;                  // name of variable
        DataTypePtr type_;                  // data type
        ValuePtr value_;                    // value
    };

    class ArrayVariable {
    public:
        ArrayVariable();
        ArrayVariable(const std::string& name);
        ~ArrayVariable();

        inline std::string GetName();
        void SetName(const std::string& name);
        
        inline DataTypePtr GetElementType();
        void SetElementType(DataTypePtr type);
        void SetElementType(DataType* type);

        ValuePtr GetValue(int num, ... );
        void AddValue(ValuePtr value);
        void AddValue(Value* value);

    private:
        std::string name_;                  // name of array variable
        DataTypePtr element_type_;          // element data type
        std::list<ValuePtr> value_list_;    // value list
        
        int array_size_;                    // product of dimension sizes
        std::list<int> dimension_list_;     // size of each dimension
    };

    class VariableTable {
    public:
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
