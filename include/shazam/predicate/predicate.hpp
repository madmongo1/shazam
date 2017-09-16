//
// Created by Richard Hodges on 15/09/2017.
//

#pragma once

#include <vector>
#include <algorithm>
#include <type_traits>
#include <utility>
#include <iostream>
#include <functional>
#include <array>

namespace shazam {


    template<class F>
    struct predicate
    {
        constexpr predicate(F f) : f_(f) {}

        template<class...Args>
        constexpr bool operator()(Args&&...args) const {
            return f_(std::forward<Args>(args)...);
        }

        constexpr F  get_function() const& { return f_; }
        constexpr F&& get_function() && { return f_; }

        F f_;
    };

    template<class F>
    constexpr auto make_predicate(F&& f)
    {
        return predicate<std::decay_t<F>>(std::forward<F>(f));
    }

    template<class F>
    constexpr auto operator not(predicate<F> const& pred)
    {
        return make_predicate([f = pred.get_function()](auto&&...args)
                              {
                                  return not f(std::forward<decltype(args)>(args)...);
                              });
    }

    template<class FL, class FR>
    constexpr auto operator and(predicate<FL> const& lpred, predicate<FR> const& rpred)
    {
        return make_predicate([fl = lpred.get_function(), fr = rpred.get_function()](auto&&...args)
                              {
                                  return fl(args...) and fr(args...);
                              });
    }

    template<class Container, class Pred>
    constexpr std::size_t count_matching(Container&& cont, Pred&& pred)
    {
        using std::begin;
        using std::end;
        using std::count_if;
        return std::count_if(begin(cont), end(cont), std::forward<Pred>(pred));
    }

    template<class T, class A, class Pred>
    auto copy_if(std::vector<T, A>const & cont, Pred&& pred)
    {
        auto matching = count_matching(cont, pred);
        std::vector<T, A> result;
        result.reserve(matching);
        std::copy_if(begin(cont), end(cont), back_inserter(result), pred);
        return result;
    }

    template<class T, class A, class Pred>
    auto copy_if(std::vector<T, A>&& cont, Pred&& pred) -> std::vector<T, A>&&
    {
        cont.erase(std::copy_if(begin(cont), end(cont), begin(cont), std::forward<Pred>(pred)), end(cont));
        return std::move(cont);
    }


    template<class T, std::size_t N, class Pred, class A = std::allocator<T>>
    auto copy_if(std::array<T, N>const & cont, Pred&& pred, A alloc = A())
    {
        auto matching = count_matching(cont, pred);
        std::vector<T, A> result(alloc);
        result.reserve(matching);
        std::copy_if(begin(cont), end(cont), back_inserter(result), pred);
        return result;
    }

    template<class T>
    constexpr auto equals(T&& t)
    {
        return make_predicate([t = std::forward<T>(t)](auto&& x)
                              {
                                  constexpr auto op = std::equal_to<>();
                                  return op(x, t);
                              });
    }

    template<class T>
    constexpr auto in_range(T&& begin, T&& end)
    {
        return make_predicate([begin = std::forward<T>(begin),
                                      end = std::forward<T>(end)](auto&& x)
                              {
                                  return std::less_equal<>()(begin, x) and std::less<>()(x, end);
                              });
    }



}