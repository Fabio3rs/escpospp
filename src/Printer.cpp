#include <algorithm>
#include <cstddef>
#include <escpospp/EscPosCommands.hpp>
#include <escpospp/MDPair.hpp>
#include <escpospp/Printer.hpp>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>

Printer::Printer(std::ostream &printerRawWriter)
    : ir(Printer::imageResolution::HIGH), printer(&printerRawWriter) {}

bool Printer::textNoMarkdown(const std::string &text) {
    raw(text);
    return true;
}

bool Printer::text(std::string text) {
    std::stack<MDPair> formats;
    std::set<MDPair> elements;
    std::string toPrint;
    for (size_t counter = 0;; counter++) {
        try {
            if (counter == text.length() - 1) {
                counter++;
                throw -2;
            }
            MDPair mode = MDPair::getMatching(text.substr(counter, 2));
            if (elements.find(mode) != elements.end() &&
                formats.top() != mode) {
                std::cout << "Incorrect text string with markdown" << std::endl;
                return false;
            }
            if (elements.find(mode) == elements.end()) {
                // First we add the characters of the string before this change
                if (counter != 0) {
                    toPrint += text.substr(0, counter);
                }
                // We apply the effect
                toPrint += mode.first;
                elements.insert(mode);
                formats.push(mode);

                // We resize the string and are ready to continue;
                text = text.substr(counter + 2, text.length() - counter - 2);
                counter = std::string::npos;
            } else if (elements.find(mode) != elements.end() &&
                       formats.top() == mode) {
                // Mode already inside, apply second sequence to string
                if (counter != 0) {
                    toPrint += text.substr(0, counter);
                }

                toPrint += mode.second;
                elements.erase(elements.find(mode));
                formats.pop();

                // We resize the string and are ready to continue;
                text = text.substr(counter + 2, text.length() - counter - 2);
                counter = std::string::npos;
            }
        } catch (int e) {
            // This means the text is still ok
            if (counter == text.length()) {
                if (!elements.empty()) {
                    std::cout << "Unmatched characters in markdown string"
                              << std::endl;
                    return false;
                }
                toPrint += text;
                break;
            }
        }
    }
    raw(toPrint);
    return true;
}

bool Printer::textCut(std::string text) {
    if (Printer::text(std::move(text))) {
        cut();
        return true;
    }
    return false;
}

void Printer::changeToTPage(char pageNum) {
    auto placeholder = EscPos::ESC + 't' + pageNum;
    raw(placeholder);
}

void Printer::raw(const std::string &text) {
    if (printer == nullptr) {
        return;
    }
    
    *printer << text;
}

void Printer::cut() { raw(EscPos::CUT); }

void Printer::image(const std::vector<std::vector<bool>> &bitmap) {
    // Quickly check the integrity of the "bitmap"
    const size_t height = bitmap.size();
    const size_t width = bitmap[0].size();
    for (size_t i = 1; i < height; i++) {
        if (width != bitmap[i].size()) {
            std::cout << "Error: the bitmap is not squared" << std::endl;
            throw -1;
        }
    }
    // First of all, set line height:
    raw(EscPos::NO_LINE);
    auto nL = static_cast<char>(width % 256); // nL
    auto nH = static_cast<char>(width / 256); // nH
    const char m = (ir == imageResolution::HIGH) ? 33 : 1;
    size_t rowCount = 0;
    size_t rowHeight = (ir == imageResolution::HIGH) ? 24 : 8;
    std::string total;
    while (rowCount < height) {
        std::string content = EscPos::BITMAP;
        // Now we configure the resolution
        content += m;
        // Notice that I can't do nL + nH because then it adds up nL and nH as
        // integers
        content += nL;
        content += nH;
        for (size_t j = 0; j < width; j++) {
            unsigned int bit = 0;
            for (size_t k = 0; k < rowHeight; k++) {
                // If we already got to the last element, then we just skip it
                // all
                if (rowCount + k < height) {
                    // Else, we shift this bit with the according position.
                    bit += ((unsigned int)bitmap[rowCount + k][j])
                           << (8U - k % 8U);
                }
                // Finally, we check if it is time to push one byte to the
                // content stream
                if (k % 8 == 7) {
                    content += static_cast<char>(bit & 0xFFU);
                    bit = 0;
                }
            }
        }
        rowCount += rowHeight;
        content += '\n';
        // raw(content);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        total += content;
    }
    raw(total);
    raw(EscPos::RESET_LINE);
}

void Printer::reset() { raw(EscPos::RESET); }
