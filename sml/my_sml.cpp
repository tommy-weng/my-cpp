#include <iostream>
#include "sml.hpp"
#include <cassert>

using std::cout;
using std::endl;

using namespace boost::sml;

// Guard
constexpr auto is_valid = [](const auto& event){ return event.valid; };

// Event
struct ack{bool valid;};
struct fin{int id; bool valid;};
struct release{};
struct timeout{};

// Dependency
struct sender
{
    template <typename T>
    constexpr void send(const T& event) const {cout << "send msg id: " << event.id << endl;}
};

// Action
constexpr auto send_fin = [](const auto& event, const sender& s) { s.send(fin{5}); };
constexpr auto send_ack = [](const auto& event, const sender& s) {s.send(event); };

// State Machine
struct tcp_release
{
    auto operator()() const
    {
        return make_transition_table (
            *"established"_s + event<release>      / send_fin = "fin wait 1"_s,
            "fin wait 1"_s + event<ack> [is_valid]            = "fin wait 2"_s,
            "fin wait 2"_s + event<fin> [is_valid] / send_ack = "time wait"_s,
            "time wait"_s + event<timeout>                    = X
        );
    }
};

int main()
{
    // Detailed tcp release refer to: http://t.zoukankan.com/viviane-p-11713253.html
    // Github: https://github.com/boost-ext/sml

    sender s{};
    sm<tcp_release> sm{s}; // pass dependencies via ctor
    assert(sm.is("established"_s));

    sm.process_event(release{}); // prints 'send: 0'
    assert(sm.is("fin wait 1"_s));

    sm.process_event(ack{true});
    assert(sm.is("fin wait 2"_s));

    sm.process_event(fin{42, true}); // prints 'send: 42'
    assert(sm.is("time wait"_s));

    sm.process_event(timeout{});
    assert(sm.is(X));

    return 0;
}