cmake_minimum_required(VERSION 3.6)
project (HeightmapGenerator VERSION 0.0.1 DESCRIPTION "Memory Visualisation Toolkit")

set(CMAKE_CXX_STANDARD 17)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
find_package( Threads REQUIRED)
find_package(OpenCV REQUIRED)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall") # -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror=unused-result -Werror=return-type")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror=unused-result -Werror=return-type")

set(HG_SOURCE_FILES 
    HeightmapGenerator/Generic.cpp
    HeightmapGenerator/Matrix.cpp
    HeightmapGenerator/Perlin.cpp
    HeightmapGenerator/Noise.cpp
)

set(HG_HEADER_FILES 
    HeightmapGenerator/Core.h
)

set(ENTRY_SOURCE_FILES 
    HGEntry/HGEntry.cpp
        )

set(ENTRY_HEADER_FILES
    HGEntry/HGEntry.h
    HGEntry/FreeImage.h
    )

include_directories(
        ${PROJECT_SOURCE_DIR}
        #${OpenCV_INCLUDE_DIRS}
        "/usr/include/"
)

MESSAGE( STATUS "dadsd:         " ${OpenCV_INCLUDE_DIRS} )
add_library(HeightGenerator SHARED ${HG_HEADER_FILES} ${HG_SOURCE_FILES})
set_target_properties(HeightGenerator PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(HeightGenerator PROPERTIES SOVERSION 1)
set_target_properties(HeightGenerator PROPERTIES PUBLIC_HEADER HeightGenerator/Core.h)
set_target_properties(HeightGenerator PROPERTIES LINKER_LANGUAGE CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lopencv_imgcodecs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lopencv_imgcodecs")

add_executable(Entry ${ENTRY_HEADER_FILES} ${ENTRY_SOURCE_FILES})
target_link_libraries(
    Entry
    HeightGenerator
    opencv_imgcodecs
    ${CMAKE_THREAD_LIBS_INIT}
    ${OpenCV_LIBRARIES}
    )


