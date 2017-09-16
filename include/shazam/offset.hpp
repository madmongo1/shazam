//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/tagged_value.hpp>
#include <cstddef>

namespace shazam {
    struct offset : tagged_value<std::size_t, class offset_tag> {
        using tagged_value<std::size_t, class offset_tag>::tagged_value;
        using tagged_value<std::size_t, class offset_tag>::value_type;
    };

    namespace literals
    {
        constexpr auto operator"" _offset(unsigned long long i) -> offset
        {
            return offset(std::size_t(i));
        }
    }

}

#include <shazam/position_math.hpp>
