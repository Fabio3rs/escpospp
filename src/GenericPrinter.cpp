#include <escpospp/GenericPrinter.hpp>

EscPos::GenericPrinter::~GenericPrinter() {
    printer.flush();
    printer.release();
}
