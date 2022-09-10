#include <escpospp/LibUsbStringBuf.hpp>
#include <escpospp/escpospp.hpp>
#include <iostream>
#include <ostream>

int main() {
    try {
        LibUsbStringBuf buf{std::pair<int, int>(0x1753, 0x0b00)};
        std::ostream stream(&buf);

        Printer printer(stream);
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.text("This is a **sample** text!\n");
        printer.cut();

        stream.flush();
        stream.flush();
        stream.flush();
        stream.flush();
    } catch (int e) {
        // There was an error
    }
    return 0;
}
