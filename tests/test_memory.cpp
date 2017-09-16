//
// Created by Richard Hodges on 16/09/2017.
//

#include <gtest/gtest.h>

#include <shazam/memory.hpp>

namespace s = shazam;
namespace sm = shazam::memory;

TEST(test_memory, null_allocator)
{

    auto alloc = sm::null_allocator();

    EXPECT_FALSE(alloc.allocate(1024));
}