#pragma once


#include <vksetup/assert.hh>

namespace vksetup {

    template<typename Derived>
    class singleton {
    public:
        using value_t = Derived;
        using value_ref_t = Derived&;
        using value_ptr_t = value_t*;

    public:
        explicit singleton() {
            ASSERT(!s_instance, "Singleton instance already exists!");
            s_instance = static_cast<value_ptr_t>(this);
        }
        static auto get() -> value_ref_t { static value_t obj{}; return *s_instance; }
        static auto ptr() -> value_ptr_t { if (!s_instance) get();  return s_instance; }
        ~singleton() = default;

    public:
        singleton(const singleton&) = delete;
        auto operator=(const singleton&) -> value_ref_t& = delete;

        singleton(singleton&&) = delete;
        auto operator=(singleton&&) -> singleton& = delete;

    protected:
        inline static value_ptr_t s_instance;
    };


}