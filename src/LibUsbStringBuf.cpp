#include <escpospp/LibUsbStringBuf.hpp>

LibUsbStringBuf::~LibUsbStringBuf() {
    int r;
    r = libusb_release_interface(printer, 0); // release the claimed interface
    if (r != 0) {
        std::cout << "Cannot Release Interface" << std::endl;
    } else {
        std::cout << "Released Interface" << std::endl;
    }

    libusb_close(printer); // close the device we opened
    libusb_exit(context);  // close the session
}
