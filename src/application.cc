#include <vksetup/application.hh>
#include <vksetup/vulkan/vulkan_context.hh>

namespace vksetup {

    auto application::init() -> bool {
        bool result{ true };

        // Init GLFW and create a window
        m_window = std::make_shared<window>(
            window_spec{
                .title = "ImGui Vulkan",
                .width = 1280,
                .height = 720,
                .allow_resize = false,
            }
        );


        return result;
    }

    auto application::run() -> void {

        while (!m_window->should_close()) {
            m_window->poll_events();

        }
        
    }

    auto application::shutdown() -> void {
        
    }
}