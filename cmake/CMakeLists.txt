set(INSTALL_PACKAGE_DIR ${INSTALL_DATA_DIR}/origin-${Origin_VERSION_MAJOR}.${Origin_VERSION_MINOR}/cmake)

# Generate package configuration and version files.
configure_package_config_file(
  OriginConfig.cmake.in
  OriginConfig.cmake
  INSTALL_DESTINATION ${INSTALL_PACKAGE_DIR}
  PATH_VARS INSTALL_BIN_DIR INSTALL_LIB_DIR INSTALL_INCLUDE_DIR
)
write_basic_package_version_file(
  OriginConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

# Export targets from the installation tree.
install(EXPORT OriginTargets DESTINATION ${INSTALL_PACKAGE_DIR})

# Install OriginConfig.cmake and OriginConfigVersion.cmake files.
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/OriginConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/OriginConfigVersion.cmake
  DESTINATION ${INSTALL_PACKAGE_DIR}
)
