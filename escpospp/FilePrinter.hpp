#pragma once

#include "GenericPrinter.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>

namespace EscPos {

class FilePrinter : public GenericPrinter {

  public:
    explicit FilePrinter(const std::string &path)
        : stream(path, std::ios::out) {
        assign(stream);
    }

    explicit FilePrinter(const std::filesystem::path &path)
        : stream(path, std::ios::out) {
        assign(stream);
    }

    explicit FilePrinter(const char *path) : stream(path, std::ios::out) {
        assign(stream);
    }

    explicit FilePrinter(std::fstream &&fstr) : stream(std::move(fstr)) {
        assign(stream);
    }

  protected:
    std::fstream stream;
};

} // namespace EscPos
