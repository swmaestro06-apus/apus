#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "vm/context.h"

namespace apus {

    class VirtualMachine {
    public:
        VirtualMachine();
        virtual ~VirtualMachine();

        void Run();

    private:
    };

}

#endif
