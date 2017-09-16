//
// Created by Richard Hodges on 16/09/2017.
//

#pragma once
#include <tuple>

namespace shazam
{
    template<class Service>
    struct service_object
    {
        using service_type = Service;
        using service_instance = typename service_type::service_instance;
        using implementation_type = typename service_type::implementation_type;

        template<class...ServiceArgs, class...CreateArgs>
        service_object(std::tuple<ServiceArgs...> &&service_args, std::tuple<CreateArgs...> &&create_args)
            : service_(service_type::apply_use(std::move(service_args))),
              impl_(get_service().apply_construct(std::move(create_args))) {}

        auto get_service() -> service_type & { return service_.get(); }


    private:
        service_instance service_;
        implementation_type impl_;
    };

}