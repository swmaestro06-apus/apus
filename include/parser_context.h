#include <list>
#include <memory>

namespace apus {

    class VirtualMachine;

    class ParserContext {
    public:

        ParserContext(std::shared_ptr<VirtualMachine> vm = nullptr);
        ~ParserContext();

        std::shared_ptr<VirtualMachine> getVM();
        void setVM(std::shared_ptr<VirtualMachine> vm);

    private:

        std::shared_ptr<VirtualMachine> vm_;

    };
}
