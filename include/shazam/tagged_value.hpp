//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

namespace shazam
{
    template<class Type, class Tag>
    struct tagged_value
    {
        using value_type = Type;
        using tag_type = Tag;

        explicit constexpr tagged_value(value_type value) : value_(value) {}

        constexpr bool operator==(tagged_value const& r) const { return value() == r.value(); }
        constexpr bool operator<(tagged_value const& r) const { return value() < r.value(); }
        constexpr bool operator>=(tagged_value const& r) const { return value() >= r.value(); }


        constexpr value_type & value() { return value_; }
        constexpr value_type const & value() const { return value_; }

    private:
        value_type value_;
    };
}