// Copyright (C) 2026 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <set>
#include <thread>

#include "routing_manager_ut_setup.hpp"

namespace {
constexpr vsomeip_v3::service_t service = 0x1234;
constexpr vsomeip_v3::instance_t instance = 0x5678;
constexpr vsomeip_v3::event_t event = 0x8001;
constexpr vsomeip_v3::client_t subscriber = 0x1001;

class late_subscription_routing_manager : public vsomeip_v3::routing_manager_impl {
public:
    explicit late_subscription_routing_manager(vsomeip_v3::routing_manager_host* _host) : routing_manager_impl(_host) { }

    bool insert_subscription_for_test(vsomeip_v3::eventgroup_t _eventgroup) {
        std::set<vsomeip_v3::event_t> its_already_subscribed_events;
        return insert_subscription(service, instance, _eventgroup, vsomeip_v3::ANY_EVENT, nullptr, subscriber,
                                   &its_already_subscribed_events);
    }

    std::function<void()> before_placeholder_creation_;

private:
    bool create_placeholder_event_and_subscribe(vsomeip_v3::service_t _service, vsomeip_v3::instance_t _instance,
                                                vsomeip_v3::eventgroup_t _eventgroup, vsomeip_v3::event_t _event,
                                                const std::shared_ptr<vsomeip_v3::debounce_filter_impl_t>& _filter,
                                                vsomeip_v3::client_t _client) override {
        if (before_placeholder_creation_) {
            before_placeholder_creation_();
        }

        const std::set<vsomeip_v3::eventgroup_t> its_eventgroups{_eventgroup};
        register_event(host_->get_client(), _service, _instance, _event, its_eventgroups, vsomeip_v3::event_type_e::ET_UNKNOWN,
                       vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, false, false,
                       true);

        const auto its_placeholder = find_event(_service, _instance, _event);
        return its_placeholder && its_placeholder->add_subscriber(_eventgroup, _filter, _client, true);
    }
};
}

TEST_F(routing_manager_ut_setup, preserves_specific_event_placeholder_subscriber_for_implicit_eventgroup) {
    const std::set<vsomeip_v3::eventgroup_t> eventgroups{event};

    its_manager->register_event(subscriber, service, instance, event, eventgroups, vsomeip_v3::event_type_e::ET_UNKNOWN,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, false,
                                false, true);

    const auto placeholder = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, placeholder);
    ASSERT_TRUE(placeholder->add_subscriber(event, nullptr, subscriber, false));

    its_manager->register_event(subscriber, service, instance, event, {}, vsomeip_v3::event_type_e::ET_EVENT,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, true,
                                false, false);

    const auto registered_event = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, registered_event);
    EXPECT_TRUE(registered_event->has_subscriber(event, subscriber));
}

TEST_F(routing_manager_ut_setup, transfers_any_event_placeholder_subscriber_for_implicit_eventgroup) {
    const std::set<vsomeip_v3::eventgroup_t> eventgroups{event};

    its_manager->register_event(subscriber, service, instance, vsomeip_v3::ANY_EVENT, eventgroups, vsomeip_v3::event_type_e::ET_UNKNOWN,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, false,
                                false, true);

    const auto placeholder = its_manager->find_event(service, instance, vsomeip_v3::ANY_EVENT);
    ASSERT_NE(nullptr, placeholder);
    ASSERT_TRUE(placeholder->add_subscriber(event, nullptr, subscriber, false));

    its_manager->register_event(subscriber, service, instance, event, {}, vsomeip_v3::event_type_e::ET_EVENT,
                                vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, true,
                                false, false);

    const auto registered_event = its_manager->find_event(service, instance, event);
    ASSERT_NE(nullptr, registered_event);
    EXPECT_TRUE(registered_event->has_subscriber(event, subscriber));
}

TEST(late_any_event_subscription, rescans_eventgroup_after_registration_overtakes_placeholder_creation) {
    boost::asio::io_context io;
    mock_routing_manager_host host;
    const std::string name("LateSubscriptionRace");
    const auto configuration = std::make_shared<vsomeip_v3::cfg::configuration_impl>("routing_manager_ut_config.json");

    EXPECT_CALL(host, get_io()).WillRepeatedly(testing::ReturnRef(io));
    EXPECT_CALL(host, get_name()).WillRepeatedly(testing::ReturnRef(name));
    EXPECT_CALL(host, get_configuration()).WillRepeatedly(testing::Return(configuration));
    EXPECT_CALL(host, get_client()).WillRepeatedly(testing::Return(0x2001));
    EXPECT_CALL(host, is_routing()).WillRepeatedly(testing::Return(false));

    late_subscription_routing_manager manager(&host);
    manager.init();

    std::mutex mutex;
    std::condition_variable condition;
    bool subscription_chose_placeholder(false);
    bool registration_complete(false);

    manager.before_placeholder_creation_ = [&] {
        std::unique_lock<std::mutex> lock(mutex);
        subscription_chose_placeholder = true;
        condition.notify_all();
        condition.wait(lock, [&] { return registration_complete; });
    };

    std::thread registration([&] {
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [&] { return subscription_chose_placeholder; });
        }

        manager.register_event(0x2001, service, instance, event, {event}, vsomeip_v3::event_type_e::ET_EVENT,
                               vsomeip_v3::reliability_type_e::RT_UNKNOWN, std::chrono::milliseconds::zero(), false, true, nullptr, true,
                               false, false);

        {
            std::lock_guard<std::mutex> lock(mutex);
            registration_complete = true;
        }
        condition.notify_all();
    });

    EXPECT_TRUE(manager.insert_subscription_for_test(event));
    registration.join();

    const auto registered_event = manager.find_event(service, instance, event);
    ASSERT_NE(nullptr, registered_event);
    EXPECT_TRUE(registered_event->has_subscriber(event, subscriber));
}
