#ifndef STATEMENT_H_
#define STATEMENT_H_

namespace apus {

    class Statement {
    public:
        
        Statement() {}
        virtual ~Statement() {}
        
        virtual void Execute() = 0;

    private:
    };

}

#endif