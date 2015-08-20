#include "vm/context.h"

namespace apus {

    Context::Context()
        : break_(false), continue_(false), return_(false), exit_(false) {
    }

    Context::~Context() {

    }

}

