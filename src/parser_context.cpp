#include "parser_context.h"

namespace apus {

    ParserContext::ParserContext() {
        // make current data type instance
        current_data_type_ = std::make_shared<DataType>();
        
        // make DataTypeTable instance and add primitive data types
        data_type_table_ = std::make_shared<DataTypeTable>();
        data_type_table_->SetPrimitiveTypes();
    }

    ParserContext::ParserContext(std::shared_ptr<VirtualMachine> vm)
        : ParserContext() {
        vm_ = vm;
    }

    ParserContext::~ParserContext() {
    }

    void ParserContext::setVM(std::shared_ptr<VirtualMachine> vm) {
        vm_ = vm;
    }

    void ParserContext::SendDataTypeTableToVM() {
        vm_->setDataTypeTable(data_type_table_);
    }

    void ParserContext::setCurrentName(const std::string& name) {
        current_name_ = name;
    }

    std::string ParserContext::getCurrentName() {
        return current_name_;
    }

    void ParserContext::setCurrentDataType(std::shared_ptr<DataType> type) {
        current_data_type_ = type;
    }

    DataTypePtr ParserContext::getCurrentDataType() {
        return current_data_type_;
    }

    // name = name of data type to be inserted
    // type_name = name of data type representing 'type'
    // e.g. struct A B (B = name, A = type_name)
    void ParserContext::AddToCurrentDataType
        (const std::string& name, const std::string& type_name) {
        current_data_type_->Insert(name, data_type_table_->Find(type_name));
    }

    // Add a primitive data type to current data type
    void ParserContext::AddToCurrentDataType
        (const std::string& name, TypeSpecifier type) {
        current_data_type_->Insert(name, data_type_table_->Find(type));
    }

    // Add a data type reference(shared_ptr) to current data type
    void ParserContext::AddToCurrentDataType
        (const std::string& name, DataTypePtr type) {
        current_data_type_->Insert(name, type);
    }

    // Add a data type reference(raw pointer) to current data type
    void ParserContext::AddToCurrentDataType
        (const std::string& name, DataType* type) {
        current_data_type_->Insert(name, type);
    }

    void ParserContext::ChangeCurrentDataType() {
        // Add current data type into data type table
        data_type_table_->Insert(current_name_, current_data_type_);

        // clear current name and reference to old current data type
        current_name_.clear();
        current_data_type_.reset();
    }
}

