#pragma once
#ifndef INCLUDE_PRINTER_H
#define INCLUDE_PRINTER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>

/*
Changed to use per instance, for example view README.md

Author: Carlos Malanche, October 2018.

This is a changed version
*/
class Printer {
  public:
    enum imageResolution { HIGH, LOW };

    explicit Printer(std::ostream &printerRawWriter);
    Printer() = default;
    ~Printer() = default;

    // Output functions
    bool textNoMarkdown(const std::string &text);
    //! Outputs semi-markdown text to printer
    bool text(std::string text);
    //! Outputs semi-markdown text to printer cutting in the end
    bool textCut(std::string text);
    //! Sends raw char stream to printer
    void raw(const std::string &text);
    //! Cuts the paper (by default, leaves some space)
    void cut();
    //! Prints an image, provided as a vector of rows of pixels.
    void image(const std::vector<std::vector<bool>> &bitmap);
    //! Set Image resolution
    void setResolution(imageResolution ir);
    //! Underline text
    void underline(bool state);
    //! Set defaults for printing
    void reset();
    // Change to T Code Page encoding
    void changeToTPage(char pageNum);

    Printer(Printer &&) = default;
    Printer &operator=(Printer &&) = default;

    Printer(const Printer &) = default;
    Printer &operator=(const Printer &) = default;

    void release() { printer = nullptr; }

    void flush() {
        if (printer != nullptr) {
            printer->flush();
        }
    }

    void assign(std::ostream &writer) {
        flush();
        printer = &writer;
    }

  private:
    imageResolution ir{imageResolution::HIGH};
    std::ostream *printer{};
};

#endif // INCLUDE_PRINTER_H
