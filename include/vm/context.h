#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>
#include <string>
#include <list>
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

    class Context {
    public:

        Context(shared_ptr<DataTypeTable> data_type_table, std::string binary_file_path);
        Context(Context* context);
        virtual ~Context();

        Context            BlockBegin();
        shared_ptr<Value>  BlockEnd();

        // Find
        shared_ptr<DataType> FindDataType(string name);
        shared_ptr<Variable> FindVariable(string name);
        shared_ptr<Function> FindFunction(string name);

        // Insert
        void InsertVariable(shared_ptr<Variable> variable);
        void InsertFunction(shared_ptr<Function> function);

        inline bool GetBreak() { return break_; }
        inline bool GetContinue() { return continue_; }
        inline bool GetReturn() { return return_; }
        inline bool GetExit() { return exit_; }
        std::shared_ptr<Value> GetReturnType() { return return_type_; }
        std::shared_ptr<Value> GetReturnValue() { return return_value_; }
        shared_ptr<DataTypeTable> GetDataTypeTable() { return data_type_table_; }
        std::string GetBinaryFilePath() { return binary_file_path_; }

        inline void SetBreak(bool _break) { break_ = _break;}
        inline void SetContinue(bool _continue) { continue_ = _continue;}
        inline void SetReturn(bool _return) { return_ = _return; }
        inline void SetExit(bool _exit) { exit_ = _exit; }
        void SetReturnType(std::shared_ptr<Value> _return_type) { return_type_ = _return_type; }
        void SetParamList(list<shared_ptr<Variable>> param_list) { param_list_ = param_list; }

    private:

        Context* parent_; // I'm not having it

        std::string binary_file_path_;

        shared_ptr<DataTypeTable> data_type_table_;
        shared_ptr<VariableTable> variable_table_;
        shared_ptr<FunctionTable> function_table_;

        list<shared_ptr<Variable>> param_list_;
        shared_ptr<Value> return_value_;

        bool break_;
        bool continue_;
        bool return_;
        bool exit_;

        std::shared_ptr<Value> return_type_;

    };

}

#endif
