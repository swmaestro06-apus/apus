#include "vm/data_type_table.h"
#include <iostream>

namespace apus {

    // DataType class

    DataType::DataType() {
        byte_size_ = 0;
        offset_ = 0;
    }

    DataType::DataType(TypeSpecifier type): DataType() {
        type_ = type;
    }

    DataType::~DataType() {
    }

    void DataType::Insert(const std::string& name, DataType* elem) {
        DataTypePtr elem_ptr(elem); // pointer to shared_ptr
        map_[name] = elem_ptr;
    }

    void DataType::Insert(const std::string& name, DataTypePtr elem) {
        map_[name] = elem;
    }

    DataTypePtr DataType::Find(const std::string& name) {
        DataTypeMap::iterator it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

    void DataType::SetByteSize(int byte_size) {
        byte_size_ = byte_size;
    }

    int DataType::GetByteSize() {
        int type_length = apus::TypeLength(type_);
        // If byte_size_ is not set
        if (byte_size_ == 0) {
            // If primitive types, get TypeLength() value
            if (type_length > 0) {
                byte_size_ = type_length;
            // If not primitive types (e.g. struct)
            } else {
                int byte_size = 0;
                // get sum of byte size of child data types
                for (DataTypeMap::iterator it = map_.begin();
                    it != map_.end(); it++) {
                    byte_size += it->second->GetByteSize();
                }
                byte_size_ = byte_size;
            }
        }
        // If byte_size_ is set, just return it
        return byte_size_;
    }
    
    void DataType::SetInitExpr(Expression* expr_ptr) {
        // pointer to shared_ptr
        init_expr_ = ExprPtr (expr_ptr);
    }

    ExprPtr DataType::GetInitExpr() {
        return init_expr_;
    }

    void DataType::SetType(TypeSpecifier type) {
        type_ = type;
    }

    TypeSpecifier DataType::GetType() {
        return type_;
    }

    bool DataType::HasChild() {
        if (map_.size() != 0) {
            return true;
        } else {
            return false;
        }
    }

    // ArrayDataType class

    ArrayDataType::ArrayDataType() : DataType() {
        array_size_ = 0;
    }

    ArrayDataType::ArrayDataType(TypeSpecifier type) 
        : DataType(type) {
        array_size_ = 0;
    }

    ArrayDataType::~ArrayDataType() {
    }


    bool ArrayDataType::IsArray() {
        if (dimension_list_.size() > 0) {
            if (array_size_ <= 1) {
                GetArraySize();
            }
            return true;
        } else {
            return false;
        }
    }

    int ArrayDataType::GetByteSize() {
        int byte_size = elem_data_type_->GetByteSize();
        // If byte_size is not set
        if (byte_size > 0) {
            // If array_size_ is set
            if (array_size_ > 1) {
                byte_size_ = byte_size * array_size_;
            // If array_size_ is not set
            } else if (dimension_list_.size() > 0) {
                byte_size_ = byte_size * GetArraySize();
            }
        }
        // If byte_size is set, just return it
        return byte_size_;
    }

    void ArrayDataType::AddDimension(int dim) {
        dimension_list_.push_front (dim);
    }

    std::list<int> ArrayDataType::GetDimensionList() {
        return dimension_list_;
    }

    void ArrayDataType::SetArraySize(int array_size) {
        array_size_ = array_size;
    }

    int ArrayDataType::GetArraySize() {
        // If array_size_ is not set
        if (array_size_ <= 1 && dimension_list_.size() > 0) {
            int array_size = 1;
            // multiply all dimension
            for (std::list<int>::iterator it = dimension_list_.begin();
                it != dimension_list_.end(); it++) {
                array_size *= *it;
            }
            if (array_size <= 1) {
                DispErr("array size cannot be less than or 1 ");
                DispErr("in DataType::SetArraySize()");
            } else {
                array_size_ = array_size;
            }
        }
        return array_size_;
    }

    void ArrayDataType::SetElement(DataTypePtr elem) {
        elem_data_type_ = elem;
    }

    void ArrayDataType::SetElement(DataType* elem) {
        // pointer to shared_ptr
        elem_data_type_ = std::make_shared<DataType>(*elem);
    }

    DataTypePtr ArrayDataType::GetElement() const {
        return elem_data_type_;
    }

    // DataTypeTable class

    DataTypeTable::DataTypeTable() {
    }

    DataTypeTable::~DataTypeTable() {
    }

    void DataTypeTable::SetPrimitiveTypes() {
        // Add primitive types into data type table's map
        for (int i = U8; i <= STR32; i++) {
            TypeSpecifier type = (TypeSpecifier) i;
            map_[apus::type_to_string[type]] = std::make_shared<DataType>(type);
        }
    }

    void DataTypeTable::Insert(const std::string& name, DataType* elem) {
        DataTypePtr elem_ptr = std::make_shared<DataType>(*elem);
        map_[name] = elem_ptr;
    }

    void DataTypeTable::Insert(const std::string& name, DataTypePtr elem) {
        map_[name] = elem;
    }

    DataTypePtr DataTypeTable::Find(const std::string& name) {
        DataTypeMap::iterator it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

    DataTypePtr DataTypeTable::Find(TypeSpecifier type) {
        DataTypeMap::iterator it = map_.find(apus::type_to_string[type]);
        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}

