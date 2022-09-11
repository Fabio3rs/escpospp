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

    ~UsbPrinter() override;

    UsbPrinter(UsbPrinter &&) = delete;
    UsbPrinter &operator=(UsbPrinter &&) = delete;

    UsbPrinter(const UsbPrinter &) = delete;
    UsbPrinter &operator=(const UsbPrinter &) = delete;

  protected:
    LibUsbStringBuf buf;
    std::ostream stream;
};

} // namespace EscPos
#endif
