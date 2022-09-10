#pragma once

#include "Printer.hpp"

#include <utility>

namespace EscPos {

class GenericPrinter {

  public:
    explicit GenericPrinter(std::ostream &printerRawWriter)
        : printer(printerRawWriter) {}
    GenericPrinter() = default;

    ~GenericPrinter() {
        printer.flush();
        printer.release();
    }

    GenericPrinter(GenericPrinter &&) = default;
    GenericPrinter &operator=(GenericPrinter &&) = default;

    GenericPrinter(const GenericPrinter &) = delete;
    GenericPrinter &operator=(const GenericPrinter &) = delete;

    // Output functions
    bool textNoMarkdown(const std::string &text) {
        return printer.textNoMarkdown(text);
    }

    bool text(std::string text) { return printer.text(std::move(text)); }

    bool textCut(std::string text) { return printer.textCut(std::move(text)); }

    void raw(const std::string &text) { printer.raw(text); }

    void cut() { printer.cut(); }

    void image(const std::vector<std::vector<bool>> &bitmap) {
        printer.image(bitmap);
    }

    void setResolution(Printer::imageResolution ir) {
        printer.setResolution(ir);
    }

    void underline(bool state) { printer.underline(state); }

    void reset() { printer.reset(); }

    void changeToTPage(char pageNum) { printer.changeToTPage(pageNum); }

    void release() { printer.release(); }

    void flush() { printer.flush(); }

    void assign(std::ostream &writer) { printer.assign(writer); }

  protected:
    Printer printer;
};

} // namespace EscPos
