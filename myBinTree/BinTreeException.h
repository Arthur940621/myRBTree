#pragma once

#include <string>
#include <stdexcept>

namespace myBinTree {

class BinTreeException final : public std::logic_error {
public:
    explicit BinTreeException(const std::string& errMsg) : logic_error(errMsg) { }
};

}
