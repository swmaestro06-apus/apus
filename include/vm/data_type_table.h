#ifndef DATA_TYPE_TABLE_H_
#define DATA_TYPE_TABLE_H_

#include <memory>
#include <string>
#include <list>
#include <map>

namespace apus {

    class DataType {
    public:
    private:
        std::string name_;
        std::list<DataType> list_;
        int size_;
    };

    class DataTypeTable {
    public:
        DataTypeTable();
        ~DataTypeTable();

        void Insert(const std::string& name, std::shared_ptr<DataType> type);
        std::shared_ptr<DataType> Find(const std::string& name);

    private:

        typedef std::map<std::string, std::shared_ptr<DataType>> DataTypeMap;
        DataTypeMap map_;
    };
}

#endif
