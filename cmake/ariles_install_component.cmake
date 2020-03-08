string(REGEX REPLACE "_" "-" ARILES_COMPONENT "${ARILES_BRIDGE}")
set(ARILES_COMPONENT_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/share/ariles-${ARILES_COMPONENT}/")

cpack_add_component(
    "${ARILES_COMPONENT}"
    DISPLAY_NAME "'${ARILES_BRIDGE}' support for ariles"
    DESCRIPTION "Enables support for '${ARILES_BRIDGE}' in ariles"
    DEPENDS "core"
    ARCHIVE_FILE "${CPACK_PACKAGE_NAME}-${ARILES_COMPONENT_NAME}-${CPACK_PACKAGE_VERSION}")


set(ariles_LIBRARIES "ariles-${ARILES_COMPONENT}_LIBRARIES")
set(ariles_INCLUDE_DIRS "ariles-${ARILES_COMPONENT}_INCLUDE_DIRS")
set(ariles_LIBRARY_DIRS "ariles-${ARILES_COMPONENT}_LIBRARY_DIRS")

set(ARILES_LIBRARIES            "${ARILES_BRIDGE_${ARILES_BRIDGE}_LIBS}")
set(ARILES_INCLUDES             "")
set(ARILES_DEPENDENCY_INCLUDES  "${ARILES_BRIDGE_${ARILES_BRIDGE}_INCLUDES}")
set(ARILES_LIBRARY_DIRS         "${ARILES_BRIDGE_${ARILES_BRIDGE}_LIBRARY_DIRS}")


if (ARILES_LIBRARIES)
    set (ARILES_SHARED_GNU_LINKER_FLAGS "-Wl,--exclude-libs")

    foreach(ARILES_LIBRARY ${ARILES_LIBRARIES})
        set(ARILES_SHARED_GNU_LINKER_FLAGS "${ARILES_SHARED_GNU_LINKER_FLAGS},${ARILES_LIBRARY}")
    endforeach(ARILES_LIBRARY)
endif (ARILES_LIBRARIES)

list(REMOVE_DUPLICATES ARILES_INCLUDES)
list(REMOVE_DUPLICATES ARILES_DEPENDENCY_INCLUDES)
list(REMOVE_DUPLICATES ARILES_LIBRARIES)
list(REMOVE_ITEM ARILES_INCLUDES "")
list(REMOVE_ITEM ARILES_DEPENDENCY_INCLUDES "")
list(REMOVE_ITEM ARILES_LIBRARIES "")


if(TARGET ${TGT_ARILES_BRIDGE_LIB})
    # built-tree specific targets, not relocatable
    #export(TARGETS ${TGT_ARILES_BRIDGE_LIB} FILE ${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}-targets.cmake)

    install(
        TARGETS ${TGT_ARILES_BRIDGE_LIB} EXPORT ${ARILES_COMPONENT}_targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT ${ARILES_COMPONENT}
    )

    install(
        EXPORT ${ARILES_COMPONENT}_targets
        DESTINATION ${ARILES_COMPONENT_CMAKE_DIR}
        COMPONENT ${ARILES_COMPONENT}
    )
endif()


if (ARILES_INCLUDES)
    configure_package_config_file(  "${PROJECT_SOURCE_DIR}/cmake/arilesConfig.cmake.in"
                                    "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}-Config.cmake"
                                    INSTALL_DESTINATION "${ARILES_COMPONENT_CMAKE_DIR}"
                                    PATH_VARS ARILES_INCLUDES
                                    NO_SET_AND_CHECK_MACRO
                                    NO_CHECK_REQUIRED_COMPONENTS_MACRO)
else()
    configure_package_config_file(  "${PROJECT_SOURCE_DIR}/cmake/arilesConfig.cmake.in"
                                    "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}Config.cmake"
                                    INSTALL_DESTINATION "${ARILES_COMPONENT_CMAKE_DIR}"
                                    NO_SET_AND_CHECK_MACRO
                                    NO_CHECK_REQUIRED_COMPONENTS_MACRO)
endif()

install(FILES "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}Config.cmake"
        DESTINATION "${ARILES_COMPONENT_CMAKE_DIR}"
        COMPONENT ${ARILES_COMPONENT})

write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    COMPATIBILITY SameMajorVersion)
install(FILES "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}ConfigVersion.cmake"
        DESTINATION "${ARILES_COMPONENT_CMAKE_DIR}"
        COMPONENT ${ARILES_COMPONENT})

if(ARILES_PKGCONFIG_INSTALL_PATH)
    string(REPLACE ";" " -I" ARILES_INCLUDES_FLAGS "${ARILES_INCLUDES}")
    set(ARILES_INCLUDES_FLAGS "-I${ARILES_INCLUDES_FLAGS}")
    string(REPLACE ";" " -l" ARILES_LIBRARIES_FLAGS "${ARILES_LIBRARIES}")
    string(REPLACE ";" " -L" ARILES_LIBRARIES_FLAGS_DIRS "${ARILES_LIBRARY_DIRS}")
    set(ARILES_LIBRARIES_FLAGS "-l${ARILES_LIBRARIES_FLAGS} -L${ARILES_LIBRARIES_FLAGS_DIRS}")
    configure_file("cmake/ariles.pc.in"             "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}.pc" @ONLY)

    install(FILES "${PROJECT_BINARY_DIR}/ariles-${ARILES_COMPONENT}.pc"
            DESTINATION "${ARILES_PKGCONFIG_INSTALL_PATH}"
            COMPONENT ${ARILES_COMPONENT})
endif()

install (DIRECTORY "${PROJECT_SOURCE_DIR}/bridges/${ARILES_BRIDGE}/ariles/"
         DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ariles/"
         COMPONENT "${ARILES_COMPONENT}")

install (DIRECTORY "${PROJECT_SOURCE_DIR}/bridges/${ARILES_BRIDGE}/ariles/"
         DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ariles/"
         COMPONENT "${ARILES_COMPONENT}")

set("DEB_CMAKE_FLAGS_${ARILES_COMPONENT}" "-DARILES_BRIDGE_${ARILES_BRIDGE}=ON -DARILES_ENABLE_CORE=OFF")
