#pragma once

#include "GenericPrinter.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace EscPos {

class StringPrinter : public GenericPrinter {

  public:
    explicit StringPrinter(const std::string &path) : stream(path) {
        assign(stream);
    }

    StringPrinter() { assign(stream); }

    explicit StringPrinter(std::stringstream &&fstr) : stream(std::move(fstr)) {
        assign(stream);
    }

    auto str() const -> std::string { return stream.str(); }
    void str(const std::string &strVal) { stream.str(strVal); }

    std::stringstream stream;
};

} // namespace EscPos
