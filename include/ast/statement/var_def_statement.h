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
        VarDefStatement(std::string type_name, std::string name);
        VarDefStatement(std::string type_name, std::string name, Expression* initializer);

        virtual ~VarDefStatement();

        virtual Type getType() override { return STMT_VAR_DEF; }
        void Execute(Context& context) override;

    private:
        TypeSpecifier type_;
        std::string type_name_;
        std::string name_;
        ExprPtr initializer_;
    };

}

#endif
