#ifndef FUNCTION_TABLE_H_
#define FUNCTION_TABLE_H_

#include <memory>
#include <string>
#include <map>
#include <list>
#include "vm/data_type_table.h"
#include "vm/context.h"

namespace apus {

    class DataType;
    class Variable;
    class Function;

    typedef std::shared_ptr<Function> FunctionPtr;
    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::shared_ptr<Variable> VariablePtr;
    typedef std::map<std::string, FunctionPtr> FunctionMap;

    class Function {
    public:
        Function();
        Function(const std::string& name);
        Function(const std::string& name, DataTypePtr return_type);
        Function(const std::string& name, DataTypePtr return_type, list<VariablePtr> arg_list);
        virtual ~Function();

        virtual std::shared_ptr<Value> Execute(Context& context) = 0;

        std::string getName() { return name_; }
        DataTypePtr getReturnType() { return return_type_; }
        list<VariablePtr> getArgList() { return arg_list_; }

    protected:
        std::string name_;
        DataTypePtr return_type_;
        list<VariablePtr> arg_list_;
    };

    class FunctionTable {
    public:
        FunctionTable();

        void Insert(std::string name, FunctionPtr function);
        FunctionPtr Find(std::string& name);

    private:
        FunctionMap map_;
    };

    class BuiltInFunction : public Function {
    public:
        virtual ~BuiltInFunction() {}
        virtual std::shared_ptr<Value> Execute(Context& context) final;
        virtual std::shared_ptr<Value> BlockBody(Context& context) = 0;
    };

    class PrintS64 : public BuiltInFunction {
    public:
        PrintS64(Context& context);
        virtual ~PrintS64();

        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class PrintSTR8 : public BuiltInFunction {
    public:
        PrintSTR8(Context& context);
        virtual ~PrintSTR8();

        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadS64 : public BuiltInFunction {
    public:
        ReadS64(Context& context);
        virtual ~ReadS64();

        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };
}

#endif
