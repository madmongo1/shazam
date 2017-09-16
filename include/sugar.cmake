sugar_include(shazam)

include(shazam_which_path)
set(shazam_interface_header_includes)
set(shazam_sep "")
foreach (hdr IN LISTS INTERFACE_HEADERS)
    shazam_which_project_path(found FILE ${hdr} PREFIX include)
    string(LENGTH "${found}" len)
    string(SUBSTRING "${hdr}" "${len}" -1 proj_rel)
    string(APPEND shazam_interface_header_includes "#include <${proj_rel}>\n")
endforeach ()

configure_file(${CMAKE_CURRENT_LIST_DIR}/shazam.hpp.in ${PROJECT_BINARY_DIR}/include/shazam.hpp)
list(APPEND ALL_HEADERS ${PROJECT_BINARY_DIR}/include/shazam.hpp)
