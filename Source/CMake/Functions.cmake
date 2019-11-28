# TODO: copy lib to bin folder
function(set_compile_options PROJECT)
    #    set_target_properties(${PROJECT}
    #        PROPERTIES
    #        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${PROJECT}"
    #        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${PROJECT}"
    #        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${PROJECT}")
endfunction()

function(link_cpf PROJECT)
    target_link_libraries(${PROJECT} cpf)
endfunction()

function(set_project_options PROJECT)
    set_compile_options(${PROJECT})
    link_cpf(${PROJECT})
endfunction()
