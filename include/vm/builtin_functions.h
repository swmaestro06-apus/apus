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

    class ReadS64 : public BuiltInFunction {
    public:
        ReadS64(Context& context);
        virtual ~ReadS64(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

    class ReadU32 : public BuiltInFunction {
    public:
        ReadU32(Context& context);
        virtual ~ReadU32(){}
        virtual std::shared_ptr<Value> BlockBody(Context& context) override;
    };

}

#endif
