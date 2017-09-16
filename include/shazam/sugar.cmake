sugar_include(predicate)
sugar_files(INTERFACE_HEADERS
        offset.hpp
        position.hpp
        position_math.hpp
        predicate.hpp
        segment.hpp
        string_service.hpp
        tagged_value.hpp)

list(APPEND ALL_HEADERS ${INTERFACE_HEADERS})

