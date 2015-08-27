#ifndef VARIABLE_TABLE_H_
#define VARIABLE_TABLE_H_

#include <memory>
#include <string>
#include <map>
#include <list>
#include <cstdarg>
#include "common/common.h"
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
        Variable(const std::string& name, DataTypePtr type);
        ~Variable();

        TypeSpecifier getType();

        std::string getName();
        void setName(const std::string& name);

        DataTypePtr getDataType();
        void setDataType(DataTypePtr type);

        VarPtr getChildVariable(const std::string& name);
        void InsertChildVariable(const std::string& name, VarPtr var);

        ValuePtr getValue();
        void setValue(ValuePtr value);

        bool IsStructVariable();

        void CreateChildVariables();

    protected:
        std::string name_;                  // name of variable
        DataTypePtr data_type_;             // data type
        VariableMap map_;                   // list of child variables
        ValuePtr value_;                    // value
    };

    class VariableTable {
    public:
        VariableTable();
        ~VariableTable();

        void Insert(const std::string name, std::shared_ptr<Variable> variable);
        std::shared_ptr<Variable> Find(const std::string& name);

    private:
        VariableMap map_;
    };
}

#endif
