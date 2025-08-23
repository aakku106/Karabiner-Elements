#pragma once

#include "logger.hpp"
#include "types.hpp"
#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDDevice.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <cstdint>
#include <pqrs/osx/iokit_hid_device.hpp>
#include <pqrs/string.hpp>
#include <string>
#include <vector>

namespace krbn {
class iokit_utility final {
public:
  static bool is_keyboard(const pqrs::osx::iokit_hid_device& device) {
    if (device.conforms_to(pqrs::hid::usage_page::generic_desktop,
                           pqrs::hid::usage::generic_desktop::keyboard)) {
      return true;
    }

    return false;
  }

  static bool is_pointing_device(const pqrs::osx::iokit_hid_device& device) {
    if (device.conforms_to(pqrs::hid::usage_page::generic_desktop,
                           pqrs::hid::usage::generic_desktop::pointer) ||
        device.conforms_to(pqrs::hid::usage_page::generic_desktop,
                           pqrs::hid::usage::generic_desktop::mouse)) {
      return true;
    }

    return false;
  }

  static bool is_game_pad(const pqrs::osx::iokit_hid_device& device) {
    if (device.conforms_to(pqrs::hid::usage_page::generic_desktop,
                           pqrs::hid::usage::generic_desktop::joystick) ||
        device.conforms_to(pqrs::hid::usage_page::generic_desktop,
                           pqrs::hid::usage::generic_desktop::game_pad)) {
      return true;
    }

    return false;
  }

  static bool is_consumer(const pqrs::osx::iokit_hid_device& device) {
    // The is_consumer property was added later, so compatibility with previous versions must be maintained.
    //
    // Typically, keyboards also confirm the consumer usage page.
    // If is_consumer returns true for a standard keyboard,
    // the device_identifiers stored in previous versions will not match the is_consumer value,
    // causing the device to be treated as a different one.
    //
    // Therefore, is_consumer will be set to true only if the device is neither a keyboard, a pointing device, nor a gamepad.
    if (is_keyboard(device) ||
        is_pointing_device(device) ||
        is_game_pad(device)) {
      return false;
    }

    if (device.conforms_to(pqrs::hid::usage_page::consumer,
                           pqrs::hid::usage::consumer::consumer_control)) {
      return true;
    }

    return false;
  }

  static bool is_karabiner_virtual_hid_device(const pqrs::hid::manufacturer_string::value_t& manufacturer,
                                              const pqrs::hid::product_string::value_t& product) {
    if (manufacturer == pqrs::hid::manufacturer_string::value_t("pqrs.org")) {
      if (pqrs::string::starts_with(type_safe::get(product), "Karabiner DriverKit VirtualHIDKeyboard") ||
          pqrs::string::starts_with(type_safe::get(product), "Karabiner DriverKit VirtualHIDPointing")) {
        return true;
      }
    }

    return false;
  }

  static std::string make_device_name(IOHIDDeviceRef _Nonnull device) {
    std::stringstream stream;
    pqrs::osx::iokit_hid_device hid_device(device);

    if (auto product_name = hid_device.find_product()) {
      stream << pqrs::string::trim_copy(type_safe::get(*product_name));
    } else {
      if (auto vendor_id = hid_device.find_vendor_id()) {
        if (auto product_id = hid_device.find_product_id()) {
          stream << std::hex
                 << "(vendor_id:0x" << type_safe::get(*vendor_id)
                 << ", product_id:0x" << type_safe::get(*product_id)
                 << ")"
                 << std::dec;
        }
      }
    }

    return stream.str();
  }

  static std::string make_device_name_for_log(device_id device_id,
                                              IOHIDDeviceRef _Nonnull device) {
    return fmt::format("{0} (device_id:{1})",
                       make_device_name(device),
                       type_safe::get(device_id));
  }
};
} // namespace krbn
