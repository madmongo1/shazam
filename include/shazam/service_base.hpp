//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once
#include <utility>
#include <tuple>

namespace shazam {

    template<class Service>
    struct service_base
    {
        template<std::size_t...Is, class Tuple>
        constexpr decltype(auto) apply_construct(std::index_sequence<Is...>, Tuple &&args)
        {
            return static_cast<Service&>(*this).construct(std::get<Is>(std::forward<Tuple>(args))...);
        }

        template<class...Args>
        constexpr decltype(auto) apply_construct(std::tuple<Args...> &&args)
        {
            return apply_construct(std::make_index_sequence<sizeof...(Args)>(),
                                   std::move(args));
        }

        template<std::size_t...Is, class Tuple>
        static constexpr decltype(auto) apply_use(std::index_sequence<Is...>, Tuple &&args)
        {
            return Service::use(std::get<Is>(std::forward<Tuple>(args))...);
        }

        template<class...Args>
        static constexpr decltype(auto) apply_use(std::tuple<Args...> &&args)
        {
            return apply_use(std::make_index_sequence<sizeof...(Args)>(),
                             std::move(args));
        }


    };
}