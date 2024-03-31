#pragma once

namespace vksetup {
    class application {
    public:

        auto init() -> bool;
        auto run() -> void;
        auto shutdown() -> void;

    };
}