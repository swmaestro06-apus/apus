#include "value.h"

namespace apus {

    std::shared_ptr<Value> SignedValue::OperateAdd(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ + (dynamic_cast<SignedValue*>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedValue::OperateSub(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ - (dynamic_cast<SignedValue*>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedValue::OperateMul(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ * (dynamic_cast<SignedValue*>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedValue::OperateDiv(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ / (dynamic_cast<SignedValue*>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedValue>(value, size);
            }
            default:
                return nullptr;
        }
    }

    std::shared_ptr<Value> SignedValue::OperateMod(const std::shared_ptr<Value> &right) const {

        switch (right->getType()) {

            case Signed: {

                int64_t value = value_ % (dynamic_cast<SignedValue*>(right.get()))->getValue();
                int     rightSize = right->getSize();
                int     size = size_ > rightSize ? size_ : rightSize;

                return std::make_shared<SignedValue>(value, size);
            }
            default:
                return nullptr;
        }
    }
}
