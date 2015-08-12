#include "vm/data_type_table.h"

namespace apus {

    void DataTypeTable::Insert (const std::string& name,
                               std::shared_ptr<DataType> type) {
        map_[name] = type;
    }

    std::shared_ptr<DataType> DataTypeTable::Find (const std::string& name) {
        DataTypeMap::iterator it = map_.find(name);

        if (it != map_.end()) {
            return it->second;
        }

        return nullptr;
    }

}
