#pragma once

#include <vksetup/singleton.hh>
#include <vksetup/singleton.hh>

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <fmt/format.h>

namespace vksetup {

    class logger : public singleton<logger> {
    public:
        logger() 
            :   m_core{ nullptr }, 
                m_app{ nullptr }  
        { 
            init(); 
        }

        auto core() -> const std::shared_ptr<spdlog::logger>& { return m_core; }
        auto app() -> const std::shared_ptr<spdlog::logger>& { return m_app; }

    private:
        auto init() -> void {
            m_core = spdlog::stdout_color_mt("CORE");
            m_app = spdlog::stdout_color_mt("APP");

            // Set m_CoreLogger pattern.
            // Check out the wiki for info about formatting
            // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
            m_core->set_pattern("%^[%X] CORE LOG [thread %t] %v%$");

            // Log every message from the current level onwards.
            // If trace is used, all messages are logged including critical ones,
            // if debug is used, trace messages aren't logged and so on.
            m_core->set_level(spdlog::level::trace);

            m_app->set_pattern("%^[%X] APP LOG [thread %t] %v%$");
            m_app->set_level(spdlog::level::trace);

            // Auto flush when "debug" or higher level message is logged on all loggers.
            // Check the FAQ for more about this matter.
            // https://github.com/gabime/spdlog/wiki/0.-FAQ
            spdlog::flush_on(spdlog::level::debug);
        }

    private:
        std::shared_ptr<spdlog::logger> m_core{};
        std::shared_ptr<spdlog::logger> m_app{};
    };
}

#if !defined(NDEBUG)
    #define ENABLE_LOGGING
#else
    #undef ENABLE_LOGGING
#endif

#if defined(ENABLE_LOGGING)
    #define CORE_LOGGER_ERROR(...) vksetup::logger::get().core()->error(fmt::format(__VA_ARGS__))
    #define CORE_LOGGER_WARN(...) vksetup::logger::get().core()->warn(fmt::format(__VA_ARGS__))
    #define CORE_LOGGER_CRITICAL(...) vksetup::logger::get().core()->critical(fmt::format(__VA_ARGS__))
    #define CORE_LOGGER_TRACE(...) vksetup::logger::get().core()->trace(fmt::format(__VA_ARGS__))
    #define CORE_LOGGER_INFO(...) vksetup::logger::get().core()->info(fmt::format(__VA_ARGS__))
    #define CORE_LOGGER_DEBUG(...) vksetup::logger::get().core()->debug(fmt::format(__VA_ARGS__))

    #define APP_LOGGER_ERROR(...) vksetup::logger::get().app()->error(fmt::format(__VA_ARGS__))
    #define APP_LOGGER_WARN(...) vksetup::logger::get().app()->warn(fmt::format(__VA_ARGS__))
    #define APP_LOGGER_CRITICAL(...) vksetup::logger::get().app()->critical(fmt::format(__VA_ARGS__))
    #define APP_LOGGER_TRACE(...) vksetup::logger::get().app()->trace(fmt::format(__VA_ARGS__))
    #define APP_LOGGER_INFO(...) vksetup::logger::get().app()->info(fmt::format(__VA_ARGS__))
    #define APP_LOGGER_DEBUG(...) vksetup::logger::get().app()->debug(fmt::format(__VA_ARGS__))
#else
    #define CORE_LOGGER_ERROR(...)
    #define CORE_LOGGER_WARN(...)
    #define CORE_LOGGER_CRITICAL(...)
    #define CORE_LOGGER_TRACE(...)
    #define CORE_LOGGER_INFO(...)
    #define CORE_LOGGER_DEBUG(...)

    #define APP_LOGGER_ERROR(...)
    #define APP_LOGGER_WARN(...)
    #define APP_LOGGER_CRITICAL(...)
    #define APP_LOGGER_TRACE(...)
    #define APP_LOGGER_INFO(...)
    #define APP_LOGGER_DEBUG(...)
#endif