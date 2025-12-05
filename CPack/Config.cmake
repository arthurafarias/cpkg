# # Tell CPack to use the External generator
# set(CPACK_GENERATOR "External")

# # Ask the External generator to perform staging (install into a temporary staging dir)
# set(CPACK_EXTERNAL_ENABLE_STAGING ON)

# # Path to our custom script (create this file below)
# set(CPACK_EXTERNAL_PACKAGE_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/CPackPKGBUILD.cmake")

# Basic package metadata (customize these)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "cxpm")
set(CPACK_PACKAGE_CONTACT "afarias.arthur@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Package Manager for C++ to C++")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_LIST_DIR}/../readme.md")