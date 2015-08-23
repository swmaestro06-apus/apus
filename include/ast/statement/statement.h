#ifndef STATEMENT_H_
#define STATEMENT_H_

#include <memory>

namespace apus {

    class Context;

    class Statement {
    public:

        enum Type {
            STMT_BLOCK = 0,
            STMT_EXPR,
            STMT_IF,
            STMT_FOR,
            STMT_BREAK,
            STMT_CONTINUE,
            STMT_RETURN,
            STMT_EXIT,
            STMT_VAR_DEF,
        };
        
        Statement() {}
        virtual ~Statement() {}

        virtual Type getType() = 0;
        virtual void Execute(Context& context) = 0;

    private:
    };

    typedef std::shared_ptr<Statement> StmtPtr;

}

#endif
