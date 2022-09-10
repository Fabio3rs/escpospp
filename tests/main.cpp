#include <escpospp/helpers.hpp>
#include <escpospp/UsbPrinter.hpp>
#include <iostream>
#include <ostream>

int main() {
    try {
        EscPos::UsbPrinter printer(std::pair<int, int>(0x1753, 0x0b00));
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.cut();

        printer.flush();
    } catch (int e) {
        // There was an error
    }
    return 0;
}
