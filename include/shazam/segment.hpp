//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/position.hpp>
#include <shazam/offset.hpp>

namespace shazam
{

    /** Represents the position and length of a segment of any array-like container.
     *
     */
    struct segment
    {
        constexpr segment(position pos, offset size) : begin_(pos), size_(size) {}

        /**
         * ensure that the segment does not extend beyond the total size of some container.
         * If necessary, reduce position() and size() until it does not
         * @param target_size
         * @return a reference to this object
         */
        constexpr segment& truncate(std::size_t target_size)
        {
            using namespace literals;
            if (begin_.value() >= target_size)
            {
                begin_ = 0_pos;
                size_ = 0_offset;
            }
            else
            {
                auto remaining = target_size - begin_.value();
                size_.value() = std::min(size_.value(), remaining);
            }

            return *this;
        }

        constexpr position end() const {
            return begin() + size();
        }

        constexpr segment until(segment limit) const
        {
            if (limit.begin() < begin())
            {
                return segment(position(0), offset(0));
            }
            else
            {
                return segment(begin(), std::min(size(), limit.begin() - begin()));
            }
        }

        constexpr segment after(segment limit) const
        {
            auto start = limit.end();
            if (start >= end())
            {
                return segment(position(0), offset(0));
            }
            else
            {
                return segment(start, offset(size() - offset(start.value())));
            }
        }


        /**
         * A segment is logcally false if it has zero size. Otherwise it is logically true.
         * This allows a range query to return a segment which indicates not found
         * @return bool
         */
        constexpr operator bool() const { return size_.value() != 0; }

        constexpr position const& begin() const { return begin_; }
        constexpr offset const& size() const { return size_; }

    private:
        position begin_;
        offset size_;
    };

    constexpr segment empty_segment = segment(position(0), offset(0));
}