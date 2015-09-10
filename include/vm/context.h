#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>
#include <list>
#include <string>
#include "ast/value/value.h"

using namespace std;

namespace apus {

    class Value;

    class DataType;
    class DataTypeTable;

    class Variable;
    class VariableTable;

    class Function;
    class FunctionTable;

    class BinaryReader;

    class Context {
    public:

        Context(shared_ptr<DataTypeTable> data_type_table, std::string binary_file_path);
        Context(Context* context);
        virtual ~Context();

        Context            BlockBegin();
        shared_ptr<Value>  BlockEnd();

        // Find
        shared_ptr<DataType> FindDataType(TypeSpecifier type);
        shared_ptr<DataType> FindDataType(string name);
        shared_ptr<Variable> FindVariable(string name);
        shared_ptr<Function> FindFunction(string name);

        // Insert
        void InsertVariable(shared_ptr<Variable> variable);
        void InsertFunction(shared_ptr<Function> function);

        inline bool GetBreak() { return *break_; }
        inline bool GetContinue() { return *continue_; }
        inline bool GetReturn() { return *return_; }
        std::shared_ptr<Value> GetReturnValue() { return return_value_; }
        shared_ptr<DataTypeTable> GetDataTypeTable() { return data_type_table_; }
        shared_ptr<BinaryReader> GetBinaryReader() { return binary_reader_; }

        inline void SetBreak(bool _break) { *break_ = _break;}
        inline void SetContinue(bool _continue) { *continue_ = _continue;}
        inline void SetReturn(bool _return) { *return_ = _return; }
        void SetReturnValue(std::shared_ptr<Value> value) { return_value_ = value; }
        void SetParamList(list<shared_ptr<Variable>> param_list) { param_list_ = param_list; }

    private:

        Context* parent_; // I'm not having it

        shared_ptr<BinaryReader> binary_reader_;

        shared_ptr<DataTypeTable> data_type_table_;
        shared_ptr<VariableTable> variable_table_;
        shared_ptr<FunctionTable> function_table_;

        list<shared_ptr<Variable>> param_list_;
        shared_ptr<Value> return_value_;

        shared_ptr<bool> break_;
        shared_ptr<bool> continue_;
        shared_ptr<bool> return_;

    };

}

#endif
