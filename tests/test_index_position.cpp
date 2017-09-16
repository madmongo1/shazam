//
// Created by Richard Hodges on 16/09/2017.
//

#include <shazam/position.hpp>
#include <shazam/position.hpp>
#include <gtest/gtest.h>

using namespace shazam::literals;

TEST(test_index_position, assignable)
{
    auto p = shazam::position(0);

    auto p2 = p - 10_offset;
    EXPECT_EQ(0_pos, p2);
    EXPECT_EQ(typeid(shazam::position), typeid(p2));

    p2 = p + 10_offset;
    EXPECT_EQ(10_pos, p2);

    EXPECT_LT(0_pos , 10_pos);

    EXPECT_EQ(0_pos, 0_pos + 10_offset - 10_offset);


}
