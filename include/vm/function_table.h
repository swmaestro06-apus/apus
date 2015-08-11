#ifndef FUNCTION_TABLE_H_
#define FUNCTION_TABLE_H_

#include <memory>
#include <string>
#include <map>

namespace apus {

    class Function;

    class FunctionData {
    public:

        FunctionData(std::string name, std::shared_ptr<Function> function)
            : name_(name), function_(function){}

        inline std::string GetName() { return name_; }
        inline std::shared_ptr<Function> GetFunction() { return function_; }

    private:

        std::string name_;
        std::shared_ptr<Function> function_;
    };

    class FunctionTable {
    public:

        typedef std::map<std::string, std::shared_ptr<FunctionData>> FunctionMap;

        FunctionTable(std::shared_ptr<FunctionTable> parent);

        void Insert(std::string name, std::shared_ptr<FunctionData> func_data);
        std::shared_ptr<FunctionData> Find(std::string& name);

        inline std::shared_ptr<FunctionTable> GetParent() { return parent_; }

    private:

        FunctionMap map_;
        std::shared_ptr<FunctionTable> parent_;
    };
}

#endif
