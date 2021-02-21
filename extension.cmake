# declare function 'set_if_not_defined'
function(set_if_not_defined variableName)
    if(NOT DEFINED ${variableName})
        if(${ARGC} EQUAL 2)
            set(${variableName} ${ARGV1} PARENT_SCOPE)
        elseif(${ARGC} GREATER 2)
            set(values)
            foreach(argv ${ARGV})
                if(NOT "${argv}" STREQUAL "${variableName}")
                    list(APPEND values "${argv}")
                endif()
            endforeach()
            set(${variableName} ${values} PARENT_SCOPE)
        else()
            set(${variableName} PARENT_SCOPE)
        endif()
    endif()
endfunction()

# declare function 'set_home_prefix'
function(set_home_prefix variableName)
    if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
        string(REPLACE "\\" "/" homePrefix "$ENV{USERPROFILE}")
    elseif("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux")
        set(homePrefix "$ENV{HOME}")
    elseif("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Darwin")
        set(homePrefix "$ENV{HOME}")
    else()
        message(
            FATAL_ERROR
            "Unable to get 'homePrefix' for CMAKE_HOST_SYSTEM_NAME: '${CMAKE_HOST_SYSTEM_NAME}'"
        )
    endif()
    set("${variableName}" "${homePrefix}" PARENT_SCOPE)
endfunction()

# declare function 'set_home_prefix_if_not_defined'
function(set_home_prefix_if_not_defined variableName)
    if(NOT DEFINED ${variableName})
        set_home_prefix(homePrefix)
        set(${variableName} ${homePrefix} PARENT_SCOPE)
    endif()
endfunction()

# declare function 'set_copy_file_command_arguments'
function(set_copy_file_command_arguments variableName)
    if(${ARGC} GREATER_EQUAL 4 AND IS_DIRECTORY ${ARGV1} AND (NOT EXISTS ${ARGV2} OR IS_DIRECTORY ${ARGV2}))
        set(names)
        foreach(i RANGE 3 ${ARGC})
            list(APPEND names ${ARGV${i}})
        endforeach()
    else()
        message(
            FATAL_ERROR
            "'set_copy_file_command_arguments' usage: set_copy_file_command_arguments(var fromDir toDir names...)"
        )
    endif()
    set(notFoundMessage "dir: ${ARGV1} not found:")
    foreach(name ${names})
        string(APPEND notFoundMessage " ${name}")
    endforeach()
    set(copyCommand "-E" "echo" ${notFoundMessage})
    foreach(name ${names})
        if(NOT DEFINED foundFile AND EXISTS "${ARGV1}/${name}" AND NOT IS_DIRECTORY "${ARGV1}/${name}")
            set(foundFile "${ARGV1}/${name}")
        endif()
    endforeach()
    if(DEFINED foundFile)
        set(copyCommand "-E" "copy" "${foundFile}" "${ARGV2}")
    endif()
    set(${variableName} ${copyCommand} PARENT_SCOPE)
endfunction()
