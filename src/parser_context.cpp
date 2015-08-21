#include "parser_context.h"
#include "vm/virtual_machine.h"

namespace apus {

    ParserContext::ParserContext(std::shared_ptr<VirtualMachine> vm)
        : vm_(vm) {

    }

    ParserContext::~ParserContext() {

    }

    std::shared_ptr<VirtualMachine> ParserContext::getVM() {
        return vm_;
    }

    void ParserContext::setVM(std::shared_ptr<VirtualMachine> vm) {
        vm_ = vm;
    }

}
