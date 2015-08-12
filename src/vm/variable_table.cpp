#include "vm/variable_table.h"

namespace apus {

    VariableTable::VariableTable(std::shared_ptr<VariableTable> parent)
        : parent_(parent) {

    }

    void VariableTable::Insert(std::string name,
                               std::shared_ptr<Variable> variable) {
        map_[name] = variable;
    }

    std::shared_ptr<Variable> VariableTable::Find(std::string& name) {
        VariableMap::iterator it = map_.find(name);

        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}
