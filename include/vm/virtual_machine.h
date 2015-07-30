#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <memory>

namespace apus {

    class Statement;

    class VirtualMachine {
    public:
        VirtualMachine();
        virtual ~VirtualMachine();

        void Run(std::vector<std::shared_ptr<apus::Statement>> instructions);
    };
}

#endif
