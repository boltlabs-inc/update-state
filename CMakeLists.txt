cmake_minimum_required (VERSION 3.0)
project (update-state)
set(NAME "update-state")

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/source_of_randomness.cmake)
include(${CMAKE_FOLDER}/cmake/threading.cmake)

find_package(emp-sh2pc REQUIRED)
include_directories(${EMP-SH2PC_INCLUDE_DIRS})

add_library(token-utils SHARED tokens/sha256.cpp tokens/hmac.cpp tokens/ecdsa.cpp tokens/tokens.cpp tokens/tokens-misc.cpp tokens/constants.cpp tokens/tx-builder.cpp tokens/test-e2e.cpp)
target_link_libraries(token-utils ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${GMP_LIBRARIES} ${EMP-OT_LIBRARIES})
   
install(TARGETS token-utils DESTINATION lib)

macro (add_test _name)
  add_executable(${_name} "test/${_name}.cpp")
  target_link_libraries(${_name}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${GMP_LIBRARIES}
    ${EMP-OT_LIBRARIES}
    ${CRYPTOPP_LIBRARIES}
    token-utils)
endmacro()

add_test(token-main)
