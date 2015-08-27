#include <ast/value/character_value.h>
#include "vm/builtin_functions.h"
#include "vm/variable_table.h"

#include "utils/BinaryReader.h"

#include "ast/value/signed_int_value.h"
#include "ast/value/unsigned_int_value.h"
#include "ast/value/string_value.h"

namespace apus {

    // Built-in Functions

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

    // READ signed int number

    ReadS8::ReadS8(Context& context) {
        name_ = "readS8";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S8"));
    }

    std::shared_ptr<Value> ReadS8::BlockBody(Context & context) {

        shared_ptr<SignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(S8, int_val);
            value = SignedIntValue::Create(context.GetDataTypeTable()->Find(S8), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadS16::ReadS16(Context& context) {
        name_ = "readS16";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S16"));
    }

    std::shared_ptr<Value> ReadS16::BlockBody(Context & context) {

        shared_ptr<SignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(S16, int_val);
            value = SignedIntValue::Create(context.GetDataTypeTable()->Find(S16), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadS32::ReadS32(Context& context) {
        name_ = "readS32";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S32"));
    }

    std::shared_ptr<Value> ReadS32::BlockBody(Context & context) {

        shared_ptr<SignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(S32, int_val);
            value = SignedIntValue::Create(context.GetDataTypeTable()->Find(S32), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadS64::ReadS64(Context& context) {
        name_ = "readS64";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S64"));
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

    // READ unsigned int value

    ReadU8::ReadU8(Context& context) {
        name_ = "readU8";
        return_type_ = context.GetDataTypeTable()->Find(std::string("U8"));
    }

    std::shared_ptr<Value> ReadU8::BlockBody(Context & context) {

        shared_ptr<UnsignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(U8, int_val);
            value = UnsignedIntValue::Create(context.GetDataTypeTable()->Find(U8), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadU16::ReadU16(Context& context) {
        name_ = "readU16";
        return_type_ = context.GetDataTypeTable()->Find(std::string("U16"));
    }

    std::shared_ptr<Value> ReadU16::BlockBody(Context & context) {

        shared_ptr<UnsignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(U16, int_val);
            value = UnsignedIntValue::Create(context.GetDataTypeTable()->Find(U16), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadU32::ReadU32(Context& context) {
        name_ = "readU32";
        return_type_ = context.GetDataTypeTable()->Find(std::string("U32"));
    }

    std::shared_ptr<Value> ReadU32::BlockBody(Context & context) {

        shared_ptr<UnsignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(U32, int_val);
            value = UnsignedIntValue::Create(context.GetDataTypeTable()->Find(U32), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadU64::ReadU64(Context& context) {
        name_ = "readU64";
        return_type_ = context.GetDataTypeTable()->Find(std::string("U64"));
    }

    std::shared_ptr<Value> ReadU64::BlockBody(Context & context) {

        shared_ptr<UnsignedIntValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint64_t int_val;
            context.GetBinaryReader()->ReadInt(U64, int_val);
            value = UnsignedIntValue::Create(context.GetDataTypeTable()->Find(U64), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    // READ character value

    ReadC8::ReadC8(Context& context) {
        name_ = "readC8";
        return_type_ = context.GetDataTypeTable()->Find(std::string("C8"));
    }

    std::shared_ptr<Value> ReadC8::BlockBody(Context & context) {

        shared_ptr<CharacterValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint32_t int_val;
            context.GetBinaryReader()->ReadChar(C8, int_val);
            value = CharacterValue::Create(context.GetDataTypeTable()->Find(C8), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadC16::ReadC16(Context& context) {
        name_ = "readC16";
        return_type_ = context.GetDataTypeTable()->Find(std::string("C16"));
    }

    std::shared_ptr<Value> ReadC16::BlockBody(Context & context) {

        shared_ptr<CharacterValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint32_t int_val;
            context.GetBinaryReader()->ReadChar(C16, int_val);
            value = CharacterValue::Create(context.GetDataTypeTable()->Find(C16), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

    ReadC32::ReadC32(Context& context) {
        name_ = "readC32";
        return_type_ = context.GetDataTypeTable()->Find(std::string("C32"));
    }

    std::shared_ptr<Value> ReadC32::BlockBody(Context & context) {

        shared_ptr<CharacterValue> value = nullptr;
        shared_ptr<BinaryReader> bin_reader = context.GetBinaryReader();

        if (bin_reader) {

            uint32_t int_val;
            context.GetBinaryReader()->ReadChar(C32, int_val);
            value = CharacterValue::Create(context.GetDataTypeTable()->Find(C32), int_val);

        }

        context.SetReturnValue(value);
        return value;
    }

}
