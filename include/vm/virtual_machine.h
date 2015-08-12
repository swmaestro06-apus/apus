#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <memory>
#include "vm/context.h"

namespace apus {

    class Context;
    class Statement;

    class VirtualMachine {
    public:
        VirtualMachine();
        virtual ~VirtualMachine();

        void Run(std::shared_ptr<DataTypeTable> data_type_table,
                 std::vector<std::shared_ptr<apus::Statement>> instructions);

    private:

        std::shared_ptr<Context> context_;

    };

}

#endif
