# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/saief1999/Documents/projects/ImageProcessing;/home/saief1999/Documents/projects/ImageProcessing/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "ImageProcessing built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/saief1999/Documents/projects/ImageProcessing/build;ImageProcessing;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin;/usr/lib/cmake/Qt6;/usr/lib/cmake/Qt6/3rdparty/extra-cmake-modules/find-modules;/usr/lib/cmake/Qt6/3rdparty/kwin")
set(CPACK_NSIS_DISPLAY_NAME "ImageProcessing 0.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "ImageProcessing 0.1.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/saief1999/Documents/projects/ImageProcessing/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ImageProcessing built using CMake")
set(CPACK_PACKAGE_FILE_NAME "ImageProcessing-0.1-linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ImageProcessing 0.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "ImageProcessing 0.1.1")
set(CPACK_PACKAGE_NAME "ImageProcessing")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "/home/saief1999/Documents/projects/ImageProcessing/License.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/saief1999/Documents/projects/ImageProcessing/build/CPackSourceConfig.cmake")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/saief1999/Documents/projects/ImageProcessing/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
