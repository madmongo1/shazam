//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/service_base.hpp>
#include <shazam/memory/block.hpp>
#include <tuple>
#include <utility>


namespace shazam { namespace memory {

    struct null_allocator_service : service_base<null_allocator_service>
    {
        struct implementation_type
        {
        };
        using service_instance = null_allocator_service;


        constexpr block allocate(implementation_type &impl, std::size_t size)
        {
            return block();
        }

        constexpr bool contains(implementation_type const &impl, block const &b)
        {
            return false;
        }

        constexpr void deallocate(implementation_type &impl, block const &b)
        {

        }

        constexpr auto get() -> null_allocator_service & { return *this; }


        constexpr implementation_type construct() { return implementation_type(); }



        /** the null_allocator_service is not dependent on any owner
         * any carries no state, so it simply returns copies of itself
         */

        static constexpr service_instance use() { return null_allocator_service(); }

    };

}}