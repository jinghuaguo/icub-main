# Copyright: (C) 2015 RobotCub Consortium
# Authors: Marco Randazzo
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

set(PROJECTNAME canLoader-console)

file(GLOB folder_source *.cpp)
file(GLOB folder_header *.h)

source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../canLoaderLib)
include_directories(${GTK2_INCLUDE_DIRS})
include_directories(${ACE_INCLUDE_DIRS})
include_directories(${icub_firmware_shared_canProtocolLib_INCLUDE_DIR})

include_directories(${icub_firmware_shared_canProtocolLib_INCLUDE_DIR}/canProtocolLib)
include_directories(${icub_firmware_shared_embobj_INCLUDE_DIR}/embobj/plus/comm-v2/icub/)
include_directories(${icub_firmware_shared_embobj_INCLUDE_DIR}/embobj/core/core)



add_executable(${PROJECTNAME} ${folder_source} ${folder_header})

target_link_libraries(${PROJECTNAME} canLoaderLib
                                     ${GTK2_LIBRARIES}
                                     ${YARP_LIBRARIES}
                                     ${ACE_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION bin)

