#pragma once

#include <string>
#include <stdexcept>

namespace myAVLTree {

class AVLTException final : public std::logic_error {
public:
    explicit AVLTException(const std::string& errMsg) : logic_error(errMsg) { }
};

}
