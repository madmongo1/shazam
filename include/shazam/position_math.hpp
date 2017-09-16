//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/position.hpp>
#include <shazam/offset.hpp>
#include <algorithm>

namespace shazam
{

    constexpr auto operator-(position l, const position& r) -> offset
    {
        if (l.value() < r.value())
            return offset(0);
        else
            return offset(l.value() - r.value());
    }

    constexpr auto operator-(offset l, const offset& r) -> offset
    {
        if (l.value() < r.value())
            return offset(0);
        else
            return offset(l.value() - r.value());
    }

    constexpr auto operator+(offset l, const offset& r) -> offset
    {
        return offset(l.value() + r.value());
    }

    constexpr auto operator-(position pos, const offset& offs) -> position
    {
        pos.value() -= std::min(offs.value(), pos.value());
        return pos;
    }

    constexpr auto operator+(position pos, const offset& offs) -> position
    {
        pos.value() += offs.value();
        return pos;
    }
}