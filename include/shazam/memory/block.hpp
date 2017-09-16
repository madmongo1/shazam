//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <tuple>
#include <utility>

namespace shazam {
    namespace memory {

        struct block
        {

            constexpr operator bool() const { return not empty(); }

            constexpr bool empty() const { return size == 0; }

            std::intptr_t address;
            std::size_t size;
        };





    }
}