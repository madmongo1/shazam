//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once
#include <shazam/memory/null_allocator_service.hpp>
#include <shazam/memory/basic_allocator.hpp>

namespace shazam { namespace memory {

    struct null_allocator : basic_allocator<null_allocator_service>
    {
        null_allocator() : basic_allocator<null_allocator_service>(std::make_tuple(), std::make_tuple()) {}
    };

}}
