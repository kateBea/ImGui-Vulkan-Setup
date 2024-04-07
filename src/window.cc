#include <vksetup/window.hh>
#include <vksetup/logger.hh>

#include <iostream>

#include <GLFW/glfw3.h>

namespace vksetup {

    window::window(const window_spec& spec) 
        :   m_title{ spec.title },
            m_width{ spec.width }, 
            m_height{ spec.height }, 
            m_resizable{ spec.allow_resize }
    {        
        init();
    }

    auto window::init() -> bool {
        // Initialize GLFW Library
        init_library();

        // Because GLFW was originally designed to create an OpenGL context,
        // we need to tell it to not create an OpenGL context with a subsequent call to glfwCreateWindow
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

#if false // To be handled when Vulkan is properly initialized

        // Allow resizing?
        if (is_resizeable()) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        }
        else {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }
#endif
        m_handle = create(window_spec{
            .title = m_title,
            .width = m_width,
            .height = m_height,
            .allow_resize = is_resizeable()
        });

        if (m_handle == nullptr) {
            return false;
        }

        install_callbacks();

        return true;
    }

    auto window::poll_events() -> void {
        glfwPollEvents();
    }

    auto window::get_title() const -> const std::string& { return m_title; }
    auto window::get_width() const -> std::int32_t { return m_width; }
    auto window::get_height() const -> std::int32_t { return m_height; }
    auto window::is_resizeable() const -> bool { return m_resizable; }
    auto window::get_handle() const -> GLFWwindow* { return m_handle; }
    auto window::should_close() const -> bool { return glfwWindowShouldClose(m_handle); }

    auto window::set_width(std::int32_t value) -> void {
        m_width = value;
    }

    auto window::set_height(std::int32_t value) -> void{
        m_height = value;
    }

    auto window::want_resizing(bool value) -> void {
        m_resizable = value;
    }

    window::~window() {
        
        destroy(m_handle);

        // Last active window shuts down the library
        if (s_window_count == 0) {
            shutdown();
        }
    }

    auto window::shutdown() -> void {
        glfwTerminate();
    }

    auto window::install_callbacks() -> void {
        // To be used within the callbacks
        glfwSetWindowUserPointer(m_handle, this);

        glfwSetCursorPosCallback(m_handle,
            []([[maybe_unused]] GLFWwindow* handle, double x, double y) -> void {
                window* data{ static_cast<window*>(glfwGetWindowUserPointer(handle)) };

                CORE_LOGGER_DEBUG("title: {}, width: {}, height: {}", 
                    data->get_title(),  data->get_width(), data->get_height());
            }
        );

    }

    auto window::init_library() -> void {
        if (!s_glfw_init_success) {
            auto ret{ glfwInit() };

            s_glfw_init_success = (ret == GLFW_TRUE);

            // Set error messages callback for GLFW
            glfwSetErrorCallback([](std::int32_t errCode, const char* desc) -> void {
                CORE_LOGGER_ERROR("GLFW error. Code: {}, Description: {}", errCode, desc);
            });
        }
    }

    auto window::destroy(GLFWwindow* window) -> void {
        // Everytime we shut down a GLFW window, we decrease the number
        // of active windows, the last GLFW window to be shutdown calls glfwTerminate()

        glfwDestroyWindow(window);
        s_window_count -= 1;
    }

    auto window::create(const window_spec& spec) -> GLFWwindow* {
        GLFWwindow* new_handle{
            glfwCreateWindow(spec.width, spec.height, spec.title.data(), nullptr, nullptr)
        };

        s_window_count += 1;

        return new_handle;
    }

}