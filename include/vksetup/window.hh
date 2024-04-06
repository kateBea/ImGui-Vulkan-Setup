#pragma once

#include <string>
#include <cstdint>
#include <atomic>

#include <glfw/glfw3.h>

namespace vksetup {

    struct window_spec {
        std::string title{};      
        std::int32_t width{};      
        std::int32_t height{};     
        bool allow_resize{}; 
    };

    class window {
    public:
        window(const window_spec& spec);

        auto poll_events() -> void;

        auto get_title() const -> const std::string&;
        auto get_width() const -> std::int32_t;
        auto get_height() const -> std::int32_t;
        auto is_resizeable() const -> bool;
        auto should_close() const -> bool;

        auto get_handle() const -> GLFWwindow*;

        auto set_width(std::int32_t value) -> void;
        auto set_height(std::int32_t value) -> void;
        auto want_resizing(bool value) -> void;

        ~window();

    private:
        auto init() -> bool;
        auto install_callbacks() -> void;

        static auto shutdown() -> void;
        static auto init_library() -> void;
        static auto destroy(GLFWwindow* window) -> void;
        static auto create(const window_spec& spec) -> GLFWwindow*;

        // Forbiden ops ===================================
        window(const window&) = delete;
        auto operator=(const window&) = delete;

        window(window&&) = delete;
        auto operator=(window&&) = delete;

    private:
        static inline std::atomic_int32_t s_window_count{};
        static inline std::atomic_bool s_glfw_init_success{};

    private:
        std::string m_title{};      
        std::int32_t m_width{};      
        std::int32_t m_height{};     
        bool m_resizable{}; 

        GLFWwindow* m_handle{};
    };

}