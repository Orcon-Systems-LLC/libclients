SET(SOURCES math.c)

# Make dynamic libm
ADD_LIBRARY(libm_dyn ${SOURCES})
SET_TARGET_PROPERTIES(libm_dyn PROPERTIES PREFIX "")
set_target_properties(libm_dyn PROPERTIES OUTPUT_NAME libm)
TARGET_LINK_DIRECTORIES(libm_dyn PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
ADD_CUSTOM_COMMAND(TARGET libm_dyn COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libm_dyn> ${CMAKE_INSTALL_PREFIX}/usr/lib/libm.so)

# Make static libm
ADD_LIBRARY(libm_static STATIC ${SOURCES})
SET_TARGET_PROPERTIES(libm_static PROPERTIES PREFIX "")
set_target_properties(libm_static PROPERTIES OUTPUT_NAME libm)
TARGET_LINK_DIRECTORIES(libm_static PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
ADD_CUSTOM_COMMAND(TARGET libm_static COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libm_static> ${CMAKE_INSTALL_PREFIX}/usr/lib/libm.a)

# Add headers target
ADD_CUSTOM_TARGET(libm_headers
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/usr/include
    COMMAND rsync -au --include '*/' --include='*.h' --include="*.hpp" --exclude='*' ${CMAKE_SOURCE_DIR}/libraries/libm/* ${CMAKE_INSTALL_PREFIX}/usr/include
)

# Combine libc_dyn and libc_static
ADD_CUSTOM_TARGET(libm)
ADD_DEPENDENCIES(libm libc libm_headers libm_dyn libm_static)
