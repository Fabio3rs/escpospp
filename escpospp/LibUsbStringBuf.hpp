#pragma once

#include <exception>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <sstream>
#include <stdexcept>
#include <sys/types.h>

class LibUsbStringBuf : public std::stringbuf {

  public:
    int sync() override {
        std::string buffer = this->str();
        int totalChars = static_cast<int>(buffer.length());
        int actual = 0;
        int r = libusb_bulk_transfer(
            printer, (1U | LIBUSB_ENDPOINT_OUT),
            reinterpret_cast<unsigned char *>(buffer.data()), totalChars,
            &actual, 0);
        if (r != 0 || actual != totalChars) {
            std::cerr << "Write Error" << std::endl;
        }

        this->str({});

        return actual;
    }

    LibUsbStringBuf(const LibUsbStringBuf &) = delete;
    LibUsbStringBuf &operator=(const LibUsbStringBuf &) = delete;

    LibUsbStringBuf(LibUsbStringBuf &&) = default;
    LibUsbStringBuf &operator=(LibUsbStringBuf &&) = default;

    // NOLINTNEXTLINE
    LibUsbStringBuf(const std::pair<int, int> &ids) {
        int r = libusb_init(&context);

        // NOLINTNEXTLINE
        libusb_set_option(context, LIBUSB_OPTION_LOG_LEVEL, 3);

        libusb_device **list = nullptr;
        ssize_t count = libusb_get_device_list(context, &list);

        for (ssize_t idx = 0; idx < count; ++idx) {
            libusb_device *device = list[idx];
            libusb_device_descriptor desc{};

            int rc = libusb_get_device_descriptor(device, &desc);

            if (rc != 0) {
                continue;
            }

            if (desc.idVendor == ids.first && desc.idProduct == ids.second) {
                libusb_open(device, &printer);
                break;
            }

            // At the moment not necessary to print debug information
            // printf("Vendor:Device = %04x:%04x\n", desc.idVendor,
            // desc.idProduct);
        }
        libusb_free_device_list(list, count);

        // A bit riskier method to open the device
        // printer = libusb_open_device_with_vid_pid(context, ids.first,
        // ids.second); //these are vendorID and productID I found for my usb
        // device
        if (printer == nullptr) {
            throw std::runtime_error("Cannot open device");
        }

        if (libusb_kernel_driver_active(printer, 0) ==
            1) { // find out if kernel driver is attached
            std::cerr << "Kernel Driver Active" << std::endl;
            if (libusb_detach_kernel_driver(printer, 0) == 0) { // detach it
                std::cerr << "Kernel Driver Detached!" << std::endl;
            }
        }

        r = libusb_claim_interface(
            printer,
            0); // claim interface 0 (the first) of device (mine had jsut 1)
        if (r < 0) {
            throw std::runtime_error("Cannot Claim Interface");
        }
    }

    ~LibUsbStringBuf() override;

  protected:
    libusb_context *context{};
    libusb_device_handle *printer{};
};
