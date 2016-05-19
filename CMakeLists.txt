cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
project (annotation_viewer)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories( ${PROJECT_SOURCE_DIR}/include )

# Opencv required
find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})
link_directories(${OPENCV_LIBRARY_DIRS})
add_definitions(${OPENCV_DEFINITIONS})

message("\n\nFound OpenCV\n\n")

# QT4 required
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

message("\n\nFound QT4\n\n")


#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set the sources needed
set( VIEWER_SOURCES
        src/customlabel.cpp
        src/main.cpp
        src/viewer.cpp
        src/viewer_read.cpp
        src/viewer_gui.cpp
        src/viewer_path.cpp
        src/viewer_input_callback.cpp
        src/viewer_update.cpp
        src/viewer_error.cpp
)

# set QT headers
SET(QT_HEADERS
    include/viewer.h
    include/customlabel.h
    )

#set QT forms
SET(QT_FORMS ui/mainwindow.ui)

# create moc for QT
QT4_WRAP_CPP(QT_MOC ${QT_HEADERS})

# process ui
QT4_WRAP_UI(QT_FORMS_HEADERS ${QT_FORMS})

ADD_EXECUTABLE(viewer ${VIEWER_SOURCES}
    ${QT_HEADERS}
    ${QT_MOC}
    ${QT_FORMS})


TARGET_LINK_LIBRARIES(viewer ${QT_LIBRARIES} ${OpenCV_LIBS})
