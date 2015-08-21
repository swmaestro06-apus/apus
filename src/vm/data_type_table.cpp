#include "vm/data_type_table.h"
#include <iostream>

namespace apus {

    // DataType class

    DataType::DataType() {
        byte_size_ = 0;
        offset_ = 0;
        array_size_ = 0;
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
            // case array
            if (array_size_ > 1) {
                byte_size_ = byte_size_ * array_size_;
            } else if (dimension_list_.size() >= 1) {
                byte_size_ = byte_size_ * GetArraySize();
            }
        }
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

    bool DataType::IsArray() {
        if (dimension_list_.size() > 0) {
            if (array_size_ <= 1) {
                GetArraySize();
            }
            return true;
        } else {
            return false;
        }
    }

    void DataType::AddDimension(int dim) {
        dimension_list_.push_front (dim);
    }

    std::list<int> DataType::GetDimensionList() {
        return dimension_list_;
    }

    void DataType::SetArraySize(int array_size) {
        array_size_ = array_size;
    }

    int DataType::GetArraySize() {
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

    // DataTypeTable class

    DataTypeTable::DataTypeTable() {
        int cur = U8;
        // Add primitive types into data type table's map
        for (cur = U8; cur <= C32; cur++) {
            TypeSpecifier type = (TypeSpecifier)cur;
            map_[apus::ToString[type]] = 
                std::make_shared<DataType>(type);
        }
    }

    DataTypeTable::~DataTypeTable() {
    }

    void DataTypeTable::Insert(const std::string& name, DataType* elem) {
        DataTypePtr elem_ptr(elem);
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
        DataTypeMap::iterator it = map_.find(apus::ToString[type]);
        if (it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }
}

