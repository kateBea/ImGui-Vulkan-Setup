#pragma once


#include <vksetup/window.hh>

#include <memory>

namespace vksetup {
    class application {
    public:

        auto init() -> bool;
        auto run() -> void;
        auto shutdown() -> void;

    private:

        std::shared_ptr<window> m_window{};

    };
}