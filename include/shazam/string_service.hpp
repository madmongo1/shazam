//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/segment.hpp>
#include <iterator>
#include <string>
#include <tuple>

namespace shazam {
    /**
     * a string service manipulates string implementations on behalf of a logic string object
     */
    struct string_service {
        using implementation_type = std::string;
        using char_type = std::string::traits_type::char_type;

        implementation_type construct(char_type const* source) {
            if (source)
                return std::string(source);
            else
                return std::string();
        }

        segment find_first(std::string const &haystack, std::string const &needle) {
            auto i = std::search(begin(haystack), end(haystack),
                                 begin(needle), end(needle));
            if (i == end(haystack))
                return empty_segment;
            else {
                return segment(position(std::distance(begin(haystack), i)), offset(needle.size()));
            }
        }

        auto make_iterators(std::string const &input, segment seg) {
            seg.truncate(input.size());
            auto first = std::next(std::begin(input), seg.begin().value());
            auto last = std::next(first, seg.size().value());
            return std::make_tuple(first, last);
        }

        std::string remove(std::string const &input, segment seg) {
            seg.truncate(input.size());
            auto result = std::string(input.get_allocator());
            if (seg) {
                auto original_seg = segment(position(0), offset(input.size()));

                auto first_seg = original_seg.until(seg);
                auto second_seg = original_seg.after(seg);

                auto result_size = first_seg.size() + second_seg.size();
                result.reserve(result_size.value());
                result.assign(input, first_seg.begin().value(), first_seg.end().value());
                result.append(input, second_seg.begin().value(), second_seg.end().value());
            }

            return result;
        }

        std::string &&remove(std::string &&input, segment seg) {

            auto iters = make_iterators(input, seg);
            input.erase(std::get<0>(iters), std::get<1>(iters));
            return std::move(input);
        }

    };

    inline string_service stringService;
}