//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once

#include <shazam/service_object.hpp>

namespace shazam { namespace memory {

    template<class Service>
    struct basic_allocator : service_object<Service>
    {
        using service_type = Service;
        using service_instance = typename service_type::service_instance;
        using implementation_type = typename service_type::implementation_type;

        using service_object<Service>::service_object;

        constexpr block allocate(std::size_t size)
        {
            return this->get_service().allocate(get_implementation(), size);
        }

        void deallocate(block const &b)
        {
            this->get_service().deallocate(get_implementation(), b);
        }

        bool contains(block const &b) const
        {
            return this->get_service().contains(get_implementation(), b);
        }

        constexpr auto get_implementation() -> implementation_type & { return impl_; }

        constexpr auto get_implementation() const -> implementation_type const & { return impl_; }

    private:
        implementation_type impl_;
    };

}}