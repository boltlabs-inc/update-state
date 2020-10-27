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

add_executable(generate-circuit tokens/generate-circuit.cpp)
target_link_libraries(generate-circuit
        ${EMP-OT_LIBRARIES}
        token-utils)

install(TARGETS generate-circuit DESTINATION bin)

install(TARGETS token-utils DESTINATION lib)
install(FILES tokens/tokens.h DESTINATION include/update-state)
install(FILES tokens/test-e2e.h DESTINATION include/update-state)

find_package(emp-ag2pc REQUIRED)
include_directories(${EMP-AG2PC_INCLUDE_DIRS})

install(FILES tokens/ag2pc/tokens.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/translation.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/test-e2e.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/sha256.h DESTINATION include/update-state/ag2pc)

add_library(tokenm-utils SHARED tokens/ag2pc/tokens.cpp tokens/ag2pc/translation.cpp)
add_library(test-e2e SHARED tokens/ag2pc/test-e2e.cpp tokens/ag2pc/translation.cpp)
target_link_libraries(tokenm-utils ${EMP-OT_LIBRARIES})
target_link_libraries(test-e2e ${EMP-OT_LIBRARIES})

install(TARGETS tokenm-utils DESTINATION lib)
install(TARGETS test-e2e DESTINATION lib)

# Test cases
macro (add_test_ag2pc _name)
  add_executable(${_name} "test/${_name}.cpp")
  target_link_libraries(${_name}
          ${EMP-OT_LIBRARIES}
          tokenm-utils)
endmacro()

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
add_test_ag2pc(tokens-main)
add_test_ag2pc(translation)
