#pragma once

#ifdef USE_LIBUSB
#include "GenericPrinter.hpp"
#include "LibUsbStringBuf.hpp"
#include <utility>

namespace EscPos {

class UsbPrinter : public GenericPrinter {

  public:
    explicit UsbPrinter(const std::pair<int, int> &device)
        : buf(device), stream(&buf) {
        assign(stream);
    }

  protected:
    LibUsbStringBuf buf;
    std::ostream stream;
};

} // namespace EscPos
#endif
