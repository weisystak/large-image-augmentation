cmake_minimum_required(VERSION 2.8)
project( simple_remap )
find_package( OpenCV REQUIRED )
add_executable( simple_remap simple_remap.cpp )
target_link_libraries( simple_remap ${OpenCV_LIBS} )

# copy image
file(GLOB Images
"${CMAKE_CURRENT_SOURCE_DIR}/images/*"
)

file(COPY
  "${Images}"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
  )