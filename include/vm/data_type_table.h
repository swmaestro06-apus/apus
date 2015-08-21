#ifndef DATA_TYPE_TABLE_H_
#define DATA_TYPE_TABLE_H_

#include "common/common.h"
#include "ast/expression.h"
#include <memory>
#include <string>
#include <list>
#include <map>
using namespace std;

namespace apus {

    class DataType;
    class Expression;

    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::shared_ptr<Expression> ExprPtr;
    typedef std::map< std::string, DataTypePtr > DataTypeMap;

    class DataType {

    public:
        DataType();
        DataType(TypeSpecifier type);
        ~DataType();

        void Insert(const std::string& name, DataType* elem);
        void Insert(const std::string& name, DataTypePtr elem);
        DataTypePtr Find(const std::string& name);

        void SetByteSize(int byte_size);
        int GetByteSize();

        void SetInitExpr(Expression* expr);
        ExprPtr GetInitExpr();

        void SetType(TypeSpecifier type);
        TypeSpecifier GetType();

        bool HasChild();

        // For an array data type
        bool IsArray();

        void AddDimension(int dim);
        std::list<int> GetDimensionList();

        void SetArraySize(int array_size);
        int GetArraySize();

    private:

        TypeSpecifier type_;            // type of the data type
        DataTypeMap map_;               // list of child data types
        int byte_size_;                 // size of bytes to be assigned
        int offset_;                    // offset in list of parent data type
        ExprPtr init_expr_;             // expression to be initialized

        // For an array data type
        int array_size_;                // product of dimension sizes
        std::list<int> dimension_list_; // containing size of each dimension 
    };

    class DataTypeTable {
    
    public:
        DataTypeTable();
        ~DataTypeTable();

        void Insert(const std::string& name, DataType* elem);
        void Insert(const std::string& name, DataTypePtr elem);
        DataTypePtr Find(const std::string& name);
        DataTypePtr Find(TypeSpecifier type);

    private:
        DataTypeMap map_;
    };

    typedef std::shared_ptr<DataTypeTable> DataTypeTablePtr;
}

#endif
