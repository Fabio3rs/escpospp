#pragma once
#ifndef INCLUDE_PRINTER_H
#define INCLUDE_PRINTER_H

#include <ostream>
#include <string>
#include <utility>
#include <vector>

/*
Singleton printer object, functions are self explained

Author: Carlos Malanche, October 2018.
*/
class Printer {
  public:
    enum imageResolution { HIGH, LOW };

    explicit Printer(std::ostream &printerRawWriter);
    ~Printer();

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
    void image(std::vector<std::vector<bool>> &bitmap);
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

  private:
    static Printer *instance;
    imageResolution ir;

    std::ostream *printer{};
};

#endif // INCLUDE_PRINTER_H
