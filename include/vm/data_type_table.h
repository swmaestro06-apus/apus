#ifndef DATA_TYPE_TABLE_H_
#define DATA_TYPE_TABLE_H_

#include "common/common.h"
#include "ast/expression.h"
#include <memory>
#include <string>
#include <list>
#include <map>
#include <cstdarg>

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
        virtual int GetByteSize();

        void SetInitExpr(Expression* expr);
        ExprPtr GetInitExpr();

        void SetType(TypeSpecifier type);
        TypeSpecifier GetType();

        bool HasChild();

    protected:
        TypeSpecifier type_;            // type of the data type
        DataTypeMap map_;               // list of child data types
        int byte_size_;                 // size of bytes to be assigned
        int offset_;                    // offset in list of parent data type
        ExprPtr init_expr_;             // expression to be initialized
    };

    class ArrayDataType : public DataType {
    public:
        ArrayDataType();
        ArrayDataType(TypeSpecifier type);
        ~ArrayDataType();

        bool IsArray();
        int GetByteSize() override;

        void AddDimension(int dim);
        std::list<int> GetDimensionList();

        void SetArraySize(int array_size);
        int GetArraySize();

        void SetElement(DataTypePtr elem);
        void SetElement(DataType* elem);
        DataTypePtr GetElement() const;

    private: 
        int array_size_;                // product of dimension sizes
        std::list<int> dimension_list_; // size of each dimension
        DataTypePtr elem_data_type_;    // element data type
    };

    class DataTypeTable {
    
    public:
        DataTypeTable();
        ~DataTypeTable();

        void SetPrimitiveTypes();

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
