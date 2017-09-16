if (SHAZAM_WHICH_PATH_INCLUDED)
    return()
endif()
set(SHAZAM_WHICH_PATH_INCLUDED 1)


include(shazam_error_checking)

function(shazam_which_path outvar)
    set(options)
    set(oneValueArgs FILE)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(wp "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    shazam_require_arg(shazam_which_path wp FILE)
    shazam_require_arg(shazam_which_path wp PATHS)

    set(found)
    foreach (prefix IN LISTS wp_PATHS)
        string(FIND "${wp_FILE}" "${prefix}" pos)
        if (pos EQUAL 0)
            set(found ${prefix})
            break()
        endif ()
    endforeach ()

    if(NOT found)
        message(FATAL_ERROR "which_path: file not found.
    file = ${wp_FILE}
    paths = ${wp_PATHS}")
    endif()

    set(${outvar} ${found} PARENT_SCOPE)

endfunction()

## given a full filename, figure out which project path its in, binary or source
##
function(shazam_which_project_path outvar)
    set(options)
    set(oneValueArgs FILE PREFIX)
    set(multiValueArgs )
    cmake_parse_arguments(wpp "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    shazam_require_arg(shazam_which_project_path wpp PREFIX)
    shazam_require_arg(shazam_which_project_path wpp FILE)

    shazam_which_path(found FILE ${wpp_FILE}
            PATHS "${PROJECT_BINARY_DIR}/${wpp_PREFIX}/" "${PROJECT_SOURCE_DIR}/${wpp_PREFIX}/")

    set(${outvar} ${found} PARENT_SCOPE)

endfunction()