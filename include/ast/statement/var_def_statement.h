#ifndef VAR_DEF_STATEMENT_H_
#define VAR_DEF_STATEMENT_H_

#include <memory>

#include "common/common.h"
#include "ast/statement/statement.h"

namespace apus {

    class Context;
    class Expression;
    class DataType;

    typedef std::shared_ptr<Expression> ExprPtr;
    typedef std::shared_ptr<DataType> DataTypePtr;

    class VarDefStatement : public Statement {
    public:

        VarDefStatement(TypeSpecifier type, std::string name);
        VarDefStatement(TypeSpecifier type, std::string name, Expression* initializer);
        VarDefStatement(DataType* data_type, std::string name, Expression* initializer);

        virtual ~VarDefStatement();

        virtual Type getType() override { return STMT_VAR_DEF; }
        void Execute(Context& context) override;

    private:
        TypeSpecifier type_;
        DataTypePtr data_type_;
        std::string name_;
        ExprPtr initializer_;
    };

}

#endif
