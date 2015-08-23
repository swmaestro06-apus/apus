#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <memory>
#include <string>
#include <list>

using namespace std;

namespace apus {

    class Value;

    class DataType;
    class DataTypeTable;

    class Variable;
    class VariableTable;

    class Context {
    public:

        Context(shared_ptr<DataTypeTable> data_type_table = nullptr);
        Context(Context* context);
        virtual ~Context();

        Context            BlockBegin();
        shared_ptr<Value>  BlockEnd();

        // Find
        shared_ptr<DataType> FindDataType(string name);
        shared_ptr<Variable> FindVariable(string name);
        // TODO : FindFunction();

        // Insert
        void InsertVariable(shared_ptr<Variable> variable);
        // TODO : InsertFunction();

        inline bool GetBreak() { return break_; }
        inline bool GetContinue() { return continue_; }
        inline bool GetReturn() { return return_; }
        inline bool GetExit() { return exit_; }

        inline void SetBreak(bool _break) { break_ = _break;}
        inline void SetContinue(bool _continue) { continue_ = _continue;}
        inline void SetReturn(bool _return) { return_ = _return; }
        inline void SetExit(bool _exit) { exit_ = _exit;}

    private:

        Context* parent_; // I'm not having it

        shared_ptr<DataTypeTable> data_type_table_;
        shared_ptr<VariableTable> variable_table_;

        list<shared_ptr<DataType>> param_list_;
        shared_ptr<Value> return_value_;

        bool break_;
        bool continue_;
        bool return_;
        bool exit_;

    };

}

#endif
