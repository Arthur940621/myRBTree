#pragma once

#include <string>
#include <stdexcept>

namespace myBSTree {

class BSTException final : public std::logic_error {
public:
    explicit BSTException(const std::string& errMsg) : logic_error(errMsg) { }
};

}