#include "test.hpp"
#include <boost/ut.hpp>

void run_event_queue_utility_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "utility::make_queue"_test = [] {
    std::vector<pqrs::osx::iokit_hid_value> hid_values;

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       1,
                                                       pqrs::hid::usage_page::keyboard_or_keypad,
                                                       pqrs::hid::usage::keyboard_or_keypad::keyboard_spacebar,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       0,
                                                       pqrs::hid::usage_page::keyboard_or_keypad,
                                                       pqrs::hid::usage::keyboard_or_keypad::keyboard_spacebar,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(3000),
                                                       1,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::mute,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(4000),
                                                       0,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::mute,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(5000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(5000),
                                                       20,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::y,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(5000),
                                                       30,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::wheel,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(5000),
                                                       40,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::ac_pan,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(6000),
                                                       -10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(6000),
                                                       -20,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::y,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(6000),
                                                       -30,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::wheel,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(6000),
                                                       -40,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::ac_pan,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(7000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(8000),
                                                       0,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    auto device_properties = krbn::device_properties::make_device_properties(krbn::device_id(1),
                                                                             nullptr);
    auto entries = krbn::event_queue::utility::make_entries(device_properties,
                                                            hid_values,
                                                            {});
    assert(entries->size() == 8);

    {
      auto& e = *((*entries)[0]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::keyboard_or_keypad,
                                   pqrs::hid::usage::keyboard_or_keypad::keyboard_spacebar));
      expect(e.get_event_type() == krbn::event_type::key_down);
    }
    {
      auto& e = *((*entries)[1]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(2000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::keyboard_or_keypad,
                                   pqrs::hid::usage::keyboard_or_keypad::keyboard_spacebar));
      expect(e.get_event_type() == krbn::event_type::key_up);
    }
    {
      auto& e = *((*entries)[2]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(3000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::consumer,
                                   pqrs::hid::usage::consumer::mute));
      expect(e.get_event_type() == krbn::event_type::key_down);
    }
    {
      auto& e = *((*entries)[3]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(4000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::consumer,
                                   pqrs::hid::usage::consumer::mute));
      expect(e.get_event_type() == krbn::event_type::key_up);
    }
    {
      auto& e = *((*entries)[4]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(5000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(10, 20, 30, 40));
      expect(e.get_event_type() == krbn::event_type::single);
    }
    {
      auto& e = *((*entries)[5]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(6000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(-10, -20, -30, -40));
      expect(e.get_event_type() == krbn::event_type::single);
    }
    {
      auto& e = *((*entries)[6]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(7000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(10, 0, 0, 0));
      expect(e.get_event_type() == krbn::event_type::single);
    }
    {
      auto& e = *((*entries)[7]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(8000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(0, 0, 0, 0));
      expect(e.get_event_type() == krbn::event_type::single);
    }
  };

  "utility::make_queue pointing_motion_xy_multiplier, pointing_motion_wheels_multiplier"_test = [] {
    std::vector<pqrs::osx::iokit_hid_value> hid_values;

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       20,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::y,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       30,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::wheel,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       40,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::ac_pan,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       -10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::x,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       -20,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::y,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       -30,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::wheel,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       -40,
                                                       pqrs::hid::usage_page::consumer,
                                                       pqrs::hid::usage::consumer::ac_pan,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    auto device_properties = krbn::device_properties::make_device_properties(krbn::device_id(1),
                                                                             nullptr);
    auto entries = krbn::event_queue::utility::make_entries(device_properties,
                                                            hid_values,
                                                            {
                                                                .pointing_motion_xy_multiplier = 2.0,
                                                                .pointing_motion_wheels_multiplier = 0.5,
                                                            });
    assert(entries->size() == 2);

    {
      auto& e = *((*entries)[0]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(20, 40, 15, 20));
      expect(e.get_event_type() == krbn::event_type::single);
    }
    {
      auto& e = *((*entries)[1]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(2000));
      expect(e.get_event().get_pointing_motion() == krbn::pointing_motion(-20, -40, -15, -20));
      expect(e.get_event_type() == krbn::event_type::single);
    }
  };

  "utility::make_queue not game_pad"_test = [] {
    std::vector<pqrs::osx::iokit_hid_value> hid_values;

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       1,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::hat_switch,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1001),
                                                       -1,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::hat_switch,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::z,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(3000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::rz,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    auto device_properties = krbn::device_properties::make_device_properties(krbn::device_id(1),
                                                                             nullptr);
    auto entries = krbn::event_queue::utility::make_entries(device_properties,
                                                            hid_values,
                                                            {});
    assert(0_ul == entries->size());
  };

  "utility::make_queue game_pad"_test = [] {
    std::vector<pqrs::osx::iokit_hid_value> hid_values;

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1000),
                                                       1,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::hat_switch,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));
    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(1001),
                                                       -1,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::hat_switch,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(2000),
                                                       10,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::z,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    hid_values.emplace_back(pqrs::osx::iokit_hid_value(krbn::absolute_time_point(3000),
                                                       20,
                                                       pqrs::hid::usage_page::generic_desktop,
                                                       pqrs::hid::usage::generic_desktop::rz,
                                                       std::nullopt, // logical_max
                                                       std::nullopt  // logical_min
                                                       ));

    auto device_properties = std::make_shared<krbn::device_properties>(krbn::device_properties::initialization_parameters{
        .device_id = krbn::device_id(1),
        .is_game_pad = true,
    });

    auto entries = krbn::event_queue::utility::make_entries(device_properties,
                                                            hid_values,
                                                            {});
    assert(4_ul == entries->size());

    {
      auto& e = *((*entries)[0]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::generic_desktop,
                                   pqrs::hid::usage::generic_desktop::dpad_up));
      expect(e.get_event_type() == krbn::event_type::key_down);
    }
    {
      auto& e = *((*entries)[1]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1000));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::generic_desktop,
                                   pqrs::hid::usage::generic_desktop::dpad_right));
      expect(e.get_event_type() == krbn::event_type::key_down);
    }
    {
      auto& e = *((*entries)[2]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1001));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::generic_desktop,
                                   pqrs::hid::usage::generic_desktop::dpad_up));
      expect(e.get_event_type() == krbn::event_type::key_up);
    }
    {
      auto& e = *((*entries)[3]);
      expect(e.get_device_id() == krbn::device_id(1));
      expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(1001));
      expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
             pqrs::hid::usage_pair(pqrs::hid::usage_page::generic_desktop,
                                   pqrs::hid::usage::generic_desktop::dpad_right));
      expect(e.get_event_type() == krbn::event_type::key_up);
    }
  };

  "utility::insert_device_keys_and_pointing_buttons_are_released_event"_test = [] {
    krbn::event_queue::event a_event(
        krbn::momentary_switch_event(pqrs::hid::usage_page::keyboard_or_keypad,
                                     pqrs::hid::usage::keyboard_or_keypad::keyboard_a));
    krbn::event_queue::event b_event(
        krbn::momentary_switch_event(pqrs::hid::usage_page::keyboard_or_keypad,
                                     pqrs::hid::usage::keyboard_or_keypad::keyboard_b));
    krbn::event_queue::event mute_event(
        krbn::momentary_switch_event(pqrs::hid::usage_page::consumer,
                                     pqrs::hid::usage::consumer::mute));
    krbn::event_queue::event button2_event(
        krbn::momentary_switch_event(pqrs::hid::usage_page::button,
                                     pqrs::hid::usage::button::button_2));

    {
      // Normal

      auto entries = std::make_shared<std::vector<krbn::event_queue::not_null_const_entry_ptr_t>>();
      auto pressed_keys_manager = std::make_shared<krbn::pressed_keys_manager>();

      PUSH_BACK_ENTRY_PTR((*entries), 1, 100, a_event, key_down, a_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 200, a_event, key_up, a_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 300, b_event, key_down, b_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 400, b_event, key_up, b_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 500, mute_event, key_down, mute_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 600, mute_event, key_up, mute_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 700, button2_event, key_down, button2_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 800, button2_event, key_up, button2_event);

      entries = krbn::event_queue::utility::insert_device_keys_and_pointing_buttons_are_released_event(entries,
                                                                                                       krbn::device_id(1),
                                                                                                       pressed_keys_manager);

      assert(entries->size() == 12); // (2 + 1) * 4

      {
        auto& e = *((*entries)[0]);
        expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
               pqrs::hid::usage_pair(pqrs::hid::usage_page::keyboard_or_keypad,
                                     pqrs::hid::usage::keyboard_or_keypad::keyboard_a));
        expect(e.get_event_type() == krbn::event_type::key_down);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(100));
      }
      {
        auto& e = *((*entries)[1]);
        expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
               pqrs::hid::usage_pair(pqrs::hid::usage_page::keyboard_or_keypad,
                                     pqrs::hid::usage::keyboard_or_keypad::keyboard_a));
        expect(e.get_event_type() == krbn::event_type::key_up);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(200));
      }
      {
        auto& e = *((*entries)[2]);
        expect(e.get_event().get_type() == krbn::event_queue::event::type::device_keys_and_pointing_buttons_are_released);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(200));
      }
      {
        auto& e = *((*entries)[3]);
        expect(e.get_event().get_if<krbn::momentary_switch_event>()->get_usage_pair() ==
               pqrs::hid::usage_pair(pqrs::hid::usage_page::keyboard_or_keypad,
                                     pqrs::hid::usage::keyboard_or_keypad::keyboard_b));
        expect(e.get_event_type() == krbn::event_type::key_down);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(300));
      }

      expect(pressed_keys_manager->empty());
    }

    {
      // Different device_id

      auto entries = std::make_shared<std::vector<krbn::event_queue::not_null_const_entry_ptr_t>>();
      auto pressed_keys_manager = std::make_shared<krbn::pressed_keys_manager>();

      PUSH_BACK_ENTRY_PTR((*entries), 1, 100, a_event, key_down, a_event);
      PUSH_BACK_ENTRY_PTR((*entries), 2, 200, a_event, key_up, a_event);

      entries = krbn::event_queue::utility::insert_device_keys_and_pointing_buttons_are_released_event(entries,
                                                                                                       krbn::device_id(1),
                                                                                                       pressed_keys_manager);

      assert(entries->size() == 2);
      expect(!pressed_keys_manager->empty());
    }

    {
      // Multiple key_down

      auto entries = std::make_shared<std::vector<krbn::event_queue::not_null_const_entry_ptr_t>>();
      auto pressed_keys_manager = std::make_shared<krbn::pressed_keys_manager>();

      PUSH_BACK_ENTRY_PTR((*entries), 1, 100, a_event, key_down, a_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 200, b_event, key_down, b_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 300, b_event, key_up, b_event);
      PUSH_BACK_ENTRY_PTR((*entries), 1, 400, a_event, key_up, a_event);

      entries = krbn::event_queue::utility::insert_device_keys_and_pointing_buttons_are_released_event(entries,
                                                                                                       krbn::device_id(1),
                                                                                                       pressed_keys_manager);

      assert(entries->size() == 5);

      {
        auto& e = *((*entries)[0]);
        expect(e.get_event() == a_event);
        expect(e.get_event_type() == krbn::event_type::key_down);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(100));
      }
      {
        auto& e = *((*entries)[1]);
        expect(e.get_event() == b_event);
        expect(e.get_event_type() == krbn::event_type::key_down);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(200));
      }
      {
        auto& e = *((*entries)[2]);
        expect(e.get_event() == b_event);
        expect(e.get_event_type() == krbn::event_type::key_up);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(300));
      }
      {
        auto& e = *((*entries)[3]);
        expect(e.get_event() == a_event);
        expect(e.get_event_type() == krbn::event_type::key_up);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(400));
      }
      {
        auto& e = *((*entries)[4]);
        expect(e.get_event().get_type() == krbn::event_queue::event::type::device_keys_and_pointing_buttons_are_released);
        expect(e.get_event_time_stamp().get_time_stamp() == krbn::absolute_time_point(400));
      }

      expect(pressed_keys_manager->empty());
    }
  };
}
