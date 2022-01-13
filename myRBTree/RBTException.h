#pragma once

#include <string>
#include <stdexcept>

namespace myRBTree {

class RBTException final : public std::logic_error {
public:
    explicit RBTException(const std::string& errMsg) : logic_error(errMsg) { }
};

}
