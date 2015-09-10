#ifndef BUILTIN_FUNCTIONS_H_
#define BUILTIN_FUNCTIONS_H_

#include <memory>
#include "vm/function_table.h"

namespace apus {

    class BuiltInFunction : public Function {
    public:
        virtual ~BuiltInFunction() {}
        virtual std::shared_ptr<Value> Execute(Context& context) final;
        virtual std::shared_ptr<Value> BlockBody(Context& context) = 0;
    };

    class PrintS64 : public BuiltInFunction {
    public:
        PrintS64(Context& context);
        virtual ~PrintS64(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class PrintSTR8 : public BuiltInFunction {
    public:
        PrintSTR8(Context& context);
        virtual ~PrintSTR8(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    // READ signed int number

    class ReadS8 : public BuiltInFunction {
    public:
        ReadS8(Context& context);
        virtual ~ReadS8(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadS16 : public BuiltInFunction {
    public:
        ReadS16(Context& context);
        virtual ~ReadS16(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadS32 : public BuiltInFunction {
    public:
        ReadS32(Context& context);
        virtual ~ReadS32(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadS64 : public BuiltInFunction {
    public:
        ReadS64(Context& context);
        virtual ~ReadS64(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    // READ unsigned int value

    class ReadU8 : public BuiltInFunction {
    public:
        ReadU8(Context& context);
        virtual ~ReadU8(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadU16 : public BuiltInFunction {
    public:
        ReadU16(Context& context);
        virtual ~ReadU16(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadU32 : public BuiltInFunction {
    public:
        ReadU32(Context& context);
        virtual ~ReadU32(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadU64 : public BuiltInFunction {
    public:
        ReadU64(Context& context);
        virtual ~ReadU64(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    // READ character value

    class ReadC8 : public BuiltInFunction {
    public:
        ReadC8(Context& context);
        virtual ~ReadC8(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadC16 : public BuiltInFunction {
    public:
        ReadC16(Context& context);
        virtual ~ReadC16(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadC32 : public BuiltInFunction {
    public:
        ReadC32(Context& context);
        virtual ~ReadC32(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };


}

#endif
