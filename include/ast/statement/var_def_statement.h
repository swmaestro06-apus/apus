#ifndef VAR_DEF_STATEMENT_H_
#define VAR_DEF_STATEMENT_H_

#include "ast/statement/statement.h"

namespace apus {

    class Context;

    class VarDefStatement : public Statement {
    public:

        VarDefStatement();
        virtual ~VarDefStatement();

        void Execute(Context& context) override;

    private:

    };

}

#endif
