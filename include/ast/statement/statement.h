#ifndef STATEMENT_H_
#define STATEMENT_H_

namespace apus {

    class Context;

    class Statement {
    public:
        
        Statement() {}
        virtual ~Statement() {}
        
        virtual void Execute(Context& context) = 0;

    private:
    };

}

#endif
