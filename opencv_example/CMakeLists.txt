cmake_minimum_required(VERSION 2.8)
project( simple_remap )
set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
find_package( OpenCV REQUIRED )
find_package(Boost 1.74 REQUIRED COMPONENTS system unit_test_framework)


add_executable( simple_remap simple_remap.cpp )
target_link_libraries( simple_remap ${OpenCV_LIBS} )


# copy image
# file(GLOB Images
# "${CMAKE_CURRENT_SOURCE_DIR}/images/*"
# )

# file(COPY
#   "${Images}"
#   DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
#   )

add_executable( roi roi.cpp)
target_link_libraries(roi ${OpenCV_LIBS})
target_compile_definitions( roi
PRIVATE
  IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/dog.jpg"
  OUTPUT_IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/partial_dog.jpg"
)

enable_testing()

add_executable(cv_test cv_test.cpp)
target_link_libraries(cv_test 
PRIVATE
  Boost::Boost
  ${OpenCV_LIBS} 
)
target_compile_definitions( cv_test
PRIVATE
  IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/dog.jpg"
  YUV_IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/YUV_dog.jpg"
  RESIZED_IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/resized_dog.jpg"
  # OUTPUT_IMG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/images/resized_dog.jpg"
)

add_test(
    NAME cv_test
    COMMAND $<TARGET_FILE:cv_test>
)