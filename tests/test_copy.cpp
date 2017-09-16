//
// Created by Richard Hodges on 15/09/2017.
//

#include <gtest/gtest.h>
#include <shazam/predicate.hpp>
#include <typeinfo>

TEST(test_copy, first)
{
    std::array<int, 10>  v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

    auto result = copy_if(v, not shazam::equals(3) and not shazam::equals(2));
    ASSERT_EQ(result, (std::vector<int>{ 1, 4, 5, 6, 7, 8, 9, 0 }));
    ASSERT_EQ(typeid(result), typeid(std::vector<int>));
/*
    result = copy_if(v, in_range(2, 8));
    check(result);

    check(copy_if(std::move(result), not equals(4)));
*/
}