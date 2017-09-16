//
// Created by Richard Hodges on 16/09/2017.
//

#include <shazam/string_service.hpp>
#include <gtest/gtest.h>

using namespace shazam::literals;


TEST(test_string_service, foo)
{

    std::string x = "the quick brown fox jumps over the lazy dog";

    auto seg = shazam::stringService.find_first(x, std::string("brown "));

    auto x2 = shazam::stringService.remove(x, seg);
    EXPECT_EQ("the quick fox jumps over the lazy dog", x2);

}