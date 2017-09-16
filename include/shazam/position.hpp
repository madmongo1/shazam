//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/tagged_value.hpp>
#include <cstddef>

namespace shazam
{
    struct position : tagged_value<std::size_t, class position_tag>
    {
        using tagged_value<std::size_t, class position_tag>::tagged_value;
        using tagged_value<std::size_t, class position_tag>::value_type;

    };

    namespace literals
    {
        constexpr auto operator"" _pos(unsigned long long i) -> position
        {
            return position(std::size_t(i));
        }
    }
}

#include <shazam/position_math.hpp>
