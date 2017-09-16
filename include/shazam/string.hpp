//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/string_service.hpp>

namespace shazam {
    template<class Service>
    struct basic_string {
        using service_type = Service;
        using implementation_type = typename service_type ::implementation_type;
        using char_type = typename service_type ::char_type;

        basic_string(char_type const* cstr)
                : impl_(get_service().construct(cstr))
                {}

        constexpr auto get_service() -> string_service& { return stringService; }
        constexpr auto get_implementation() const -> implementation_type const& { return impl_; }
        constexpr auto get_implementation() -> implementation_type & { return impl_; }
    private:
        implementation_type impl_;
    };

    using string = basic_string<string_service>;

}