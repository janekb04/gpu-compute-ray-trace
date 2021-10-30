file(GLOB files "*")
foreach(file ${files})
    cmake_path(GET file FILENAME file)
    if (MSVC)
        configure_file("${file}" "../Debug/${file}" COPYONLY) # todo: handle release
    else()
        configure_file("${file}" "../${file}" COPYONLY)
    endif()
endforeach()

