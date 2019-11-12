project(cpf)
include(CMakeSources.cmake)

if(STATIC_LIB)
    add_library(cpf STATIC ${CPF_SRCS})
else()
    add_library(cpf SHARED ${CPF_SRCS})
endif()

target_compile_definitions(cpf 
    PRIVATE -DEXPORTS)
target_include_directories(cpf
    PUBLIC .)
target_link_libraries(cpf
    PUBLIC )
set_compile_options(cpf)
