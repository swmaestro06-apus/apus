#include "ast/statement/var_def_statement.h"

#include "ast/value/value.h"
#include "ast/value/signed_int_value.h"
#include "ast/value/float_value.h"

#include "vm/variable_table.h"
#include "vm/context.h"

namespace apus {

    VarDefStatement::VarDefStatement(TypeSpecifier type, std::string name)
        : VarDefStatement(type, nullptr, name, nullptr) {
    }

    VarDefStatement::VarDefStatement(TypeSpecifier type, std::string name, Expression* initializer)
        : VarDefStatement(type, nullptr, name, initializer) {
    }

    VarDefStatement::VarDefStatement(TypeSpecifier type, DataType* data_type, std::string name, Expression* initializer)
        : type_(type), data_type_(data_type), name_(name), initializer_(initializer) {
    }

    VarDefStatement::~VarDefStatement() {

    }

    void VarDefStatement::Execute(Context& context) {

        std::shared_ptr<Variable> var = std::make_shared<Variable>(name_);

        if (data_type_) {
            var->setDataType(data_type_);
        }

        if (initializer_) {
            var->setValue(initializer_->Evaluate(context));
        }

        else {
            var->setValue(nullptr);
        }

    }

}
