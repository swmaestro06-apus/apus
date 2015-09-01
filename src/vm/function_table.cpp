#include "vm/function_table.h"
#include "vm/variable_table.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/string_value.h"

#include "utils/BinaryReader.h"

#include "vm/function_table.h"

namespace apus {

    // Function class

    Function::Function() {
    }

    Function::Function(const std::string& name) {
        name_ = name;
        return_type_ = nullptr;
    }

    Function::Function(const std::string& name, DataTypePtr return_type) {
        name_ = name;
        return_type_ = return_type;
    }

    Function::Function(const std::string& name, DataTypePtr return_type, list<VariablePtr> arg_list) {
        name_ = name;
        return_type_ = return_type;
        arg_list_ = arg_list;
    }

    Function::~Function() {
    }

    // FunctionTable class

    FunctionTable::FunctionTable() {

    }
    void FunctionTable::Insert(std::string name,
                               std::shared_ptr<Function> function) {
        map_[name] = function;
    }

    std::shared_ptr<Function> FunctionTable::Find(std::string& name) {
        FunctionMap::iterator it = map_.find(name);

        if(it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Built-in Function

    std::shared_ptr<Value> BuiltInFunction::Execute(Context &context) {

        Context child = context.BlockBegin();

        this->BlockBody(child);

        child.BlockEnd();
        return context.GetReturnValue();
    }

    PrintS64::PrintS64(Context& context) {
        name_ = "printS64";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S64"));

        VariablePtr arg =
                std::make_shared<Variable>(
                        std::string("val"),
                        context.GetDataTypeTable()->Find(S64)
                );

        arg_list_.push_back(arg);
    }

    PrintS64::~PrintS64() {
    }

    std::shared_ptr<Value> PrintS64::BlockBody(Context & context) {

        ValuePtr value = nullptr;
        VariablePtr var = context.FindVariable("val");

        if (var) {
            value = var->getValue();

            int64_t int_val = std::dynamic_pointer_cast<SignedIntValue>(value)->getIntValue();
            cout << int_val << endl;

            context.SetReturnValue(value);
        }
        return value;
    }


    PrintSTR8::PrintSTR8(Context& context) {
        name_ = "printSTR8";
        return_type_ = context.GetDataTypeTable()->Find(STR8);

        VariablePtr arg =
                std::make_shared<Variable>(
                        std::string("val"),
                        context.GetDataTypeTable()->Find(STR8)
                );

        arg_list_.push_back(arg);
    }

    PrintSTR8::~PrintSTR8() {
    }

    std::shared_ptr<Value> PrintSTR8::BlockBody(Context & context) {

        ValuePtr value = nullptr;
        VariablePtr var = context.FindVariable("val");

        if (var) {
            value = var->getValue();

            std::string str_val = std::dynamic_pointer_cast<StringValue>(value)->getStringValue();
            cout << str_val << endl;

            context.SetReturnValue(value);
        }

        return value;
    }

    ReadS64::ReadS64(Context& context) {
        name_ = "readS64";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S64"));
    }

    ReadS64::~ReadS64() {
    }

    std::shared_ptr<Value> ReadS64::BlockBody(Context & context) {

        shared_ptr<SignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(S64, int_val);
            value = SignedIntValue::Create(context.GetDataTypeTable()->Find(S64), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }


}
