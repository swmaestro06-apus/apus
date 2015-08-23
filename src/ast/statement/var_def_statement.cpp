#include "ast/statement/var_def_statement.h"

#include "ast/value/value.h"

#include "vm/variable_table.h"
#include "vm/context.h"

namespace apus {

    VarDefStatement::VarDefStatement(TypeSpecifier type, std::string name) {
        type_ = type;
        type_name_ = "";
        name_ = name;
        initializer_ = nullptr;
    }

    VarDefStatement::VarDefStatement(TypeSpecifier type, std::string name, Expression* initializer) {
        type_ = type;
        type_name_ = "";
        name_ = name;
        initializer_ = ExprPtr(initializer);
    }

    VarDefStatement::VarDefStatement(std::string type_name,
                                     std::string name) {
        type_ = NOT_DEFINED;
        type_name_ = type_name;
        name_ = name;
        initializer_ = nullptr;
    }

    VarDefStatement::VarDefStatement(std::string type_name, std::string name,
                                     Expression *initializer) {
        type_ = NOT_DEFINED;
        type_name_ = type_name;
        name_ = name;
        initializer_ = ExprPtr(initializer);
    }

    VarDefStatement::~VarDefStatement() {

    }

    void VarDefStatement::Execute(Context& context) {

        std::shared_ptr<Variable> var = nullptr;

        if (type_ != NOT_DEFINED) {
            var = std::make_shared<Variable>(name_, context.FindDataType(type_));
        }
        else {
            var = std::make_shared<Variable>(name_, context.FindDataType(type_name_));
        }

        if (initializer_) {
            var->setValue(initializer_->Evaluate(context));
        }

        else {
            var->setValue(nullptr);
        }

    }

}
