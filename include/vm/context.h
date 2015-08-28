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

    class Context {
    public:

        Context(shared_ptr<DataTypeTable> data_type_table = nullptr);
        Context(Context* context);
        virtual ~Context();

        Context            BlockBegin();
        shared_ptr<Value>  BlockEnd();

        // Find
        shared_ptr<DataType> FindDataType(TypeSpecifier type);
        shared_ptr<DataType> FindDataType(string name);
        shared_ptr<Variable> FindVariable(string name);
        // TODO : FindFunction();

        // Insert
        void InsertVariable(shared_ptr<Variable> variable);
        // TODO : InsertFunction();

        inline bool GetBreak() { return *break_; }
        inline bool GetContinue() { return *continue_; }
        inline bool GetReturn() { return *return_; }

        inline void SetBreak(bool _break) { *break_ = _break;}
        inline void SetContinue(bool _continue) { *continue_ = _continue;}
        inline void SetReturn(bool _return) { *return_ = _return; }

    private:

        Context* parent_; // I'm not having it

        shared_ptr<DataTypeTable> data_type_table_;
        shared_ptr<VariableTable> variable_table_;

        list<shared_ptr<DataType>> param_list_;
        shared_ptr<Value> return_value_;

        shared_ptr<bool> break_;
        shared_ptr<bool> continue_;
        shared_ptr<bool> return_;

    };

}

#endif
