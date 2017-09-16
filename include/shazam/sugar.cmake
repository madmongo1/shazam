sugar_include(memory)
sugar_include(predicate)
sugar_files(INTERFACE_HEADERS
        memory.hpp
        offset.hpp
        position.hpp
        position_math.hpp
        predicate.hpp
        segment.hpp
        service_base.hpp
        service_object.hpp
        string.hpp
        string_service.hpp
        tagged_value.hpp)

list(APPEND ALL_HEADERS ${INTERFACE_HEADERS})

