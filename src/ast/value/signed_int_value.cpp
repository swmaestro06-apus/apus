#include <ast/value/signed_int_value.h>

namespace apus {

    std::shared_ptr<Value> SignedIntValue::OperateADD(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ + dynamic_cast<SignedIntValue *>(right.get())->getValue();
                int     right_size = right->getSize();
                int     size = size_ > right_size ? size_ : right_size;

                return std::make_shared<SignedIntValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedIntValue::OperateSUB(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ - (dynamic_cast<SignedIntValue *>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedIntValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedIntValue::OperateMUL(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ * (dynamic_cast<SignedIntValue *>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedIntValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedIntValue::OperateDIV(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ / (dynamic_cast<SignedIntValue *>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedIntValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedIntValue::OperateMOD(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ % (dynamic_cast<SignedIntValue *>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedIntValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

}