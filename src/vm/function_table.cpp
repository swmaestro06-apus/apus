#include "vm/function_table.h"
#include "ast/function.h"

namespace apus {

    FunctionTable::FunctionTable(std::shared_ptr<FunctionTable> parent)
        : parent_(parent) {

    }

    void FunctionTable::Insert(std::string name,
                               std::shared_ptr<FunctionData> func_data) {
        map_[name] = func_data;
    }

    std::shared_ptr<FunctionData> FunctionTable::Find(std::string & name) {
        FunctionMap::iterator it = map_.find(name);

        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

}
