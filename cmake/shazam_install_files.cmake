if (SHAZAM_INSTALL_FILES_INCLUDED)
    return()
endif ()
set(SHAZAM_INSTALL_FILES_INCLUDED 1)

include(shazam_error_checking)
include(shazam_which_path)


function(shazam_install_files)
    set(options)
    set(oneValueArgs DESTINATION SOURCE)
    set(multiValueArgs FILES)
    cmake_parse_arguments(sif "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})


    shazam_require_arg(shazam_install_files sif DESTINATION)
    shazam_require_arg(shazam_install_files sif SOURCE)
    shazam_require_arg(shazam_install_files sif FILES)

    foreach (file IN LISTS sif_FILES)
        shazam_which_path(found
                FILE ${file}
                PATHS "${PROJECT_BINARY_DIR}/${sif_SOURCE}/" "${PROJECT_SOURCE_DIR}/${sif_SOURCE}/")
        string(LENGTH "${found}" len)
        string(SUBSTRING "${file}" ${len} -1 relative_file)
        get_filename_component(reldir ${relative_file} DIRECTORY)
        if (reldir)
            install(FILES ${file} DESTINATION "${sif_DESTINATION}/${reldir}")
        else ()
            install(FILES ${file} DESTINATION "${sif_DESTINATION}")
        endif ()
    endforeach ()

endfunction()
