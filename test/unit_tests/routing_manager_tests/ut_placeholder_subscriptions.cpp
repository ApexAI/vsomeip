// Copyright (C) 2026 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <chrono>
#include <set>

#include "routing_manager_ut_setup.hpp"

namespace {
constexpr vsomeip_v3::service_t service = 0x1234;
constexpr vsomeip_v3::instance_t instance = 0x5678;
constexpr vsomeip_v3::event_t event = 0x8001;
constexpr vsomeip_v3::client_t subscriber = 0x1001;
}

TEST_F(routing_manager_ut_setup, preserves_specific_event_placeholder_subscriber_for_implicit_eventgroup) {
    const std::set<vsomeip_v3::eventgroup_t> eventgroups{event};

    its_manager->register_event(subscriber, service, instance, event, eventgroups, vsomeip_v3::event_type_e::ET_UNKNOWN,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr,
                                false, false, true);

    const auto placeholder = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, placeholder);
    ASSERT_TRUE(placeholder->add_subscriber(event, nullptr, subscriber, false));

    its_manager->register_event(subscriber, service, instance, event, {}, vsomeip_v3::event_type_e::ET_EVENT,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr,
                                true, false, false);

    const auto registered_event = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, registered_event);
    EXPECT_TRUE(registered_event->has_subscriber(event, subscriber));
}

TEST_F(routing_manager_ut_setup, transfers_any_event_placeholder_subscriber_for_implicit_eventgroup) {
    const std::set<vsomeip_v3::eventgroup_t> eventgroups{event};

    its_manager->register_event(subscriber, service, instance, vsomeip_v3::ANY_EVENT, eventgroups,
                                vsomeip_v3::event_type_e::ET_UNKNOWN, vsomeip_v3::reliability_type_e::RT_UNKNOWN,
                                std::chrono::milliseconds::zero(), false, true, nullptr, false, false, true);

    const auto placeholder = its_manager->find_event(service, instance, vsomeip_v3::ANY_EVENT);
    ASSERT_NE(nullptr, placeholder);
    ASSERT_TRUE(placeholder->add_subscriber(event, nullptr, subscriber, false));

    its_manager->register_event(subscriber, service, instance, event, {}, vsomeip_v3::event_type_e::ET_EVENT,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr,
                                true, false, false);

    const auto registered_event = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, registered_event);
    EXPECT_TRUE(registered_event->has_subscriber(event, subscriber));
}
