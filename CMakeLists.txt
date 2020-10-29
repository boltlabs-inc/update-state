cmake_minimum_required (VERSION 3.0)
project (update-state)
set(NAME "update-state")

# GMP
# https://raw.githubusercontent.com/stevedekorte/io/master/modules/FindGMP.cmake

# Try to find the GMP librairies
# GMP_FOUND - system has GMP lib
# GMP_INCLUDE_DIR - the GMP include directory
# GMP_LIBRARIES - Libraries needed to use GMP

if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
  # Already in cache, be silent
  set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

find_path(GMP_INCLUDE_DIR NAMES gmp.h )
find_library(GMP_LIBRARIES NAMES gmp libgmp )
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx )
MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES} )

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)
# end of GMP

find_path(CMAKE_FOLDER NAMES cmake/emp-tool-config.cmake)
include(${CMAKE_FOLDER}/cmake/common.cmake)
include(${CMAKE_FOLDER}/cmake/enable_rdseed.cmake)
include(${CMAKE_FOLDER}/cmake/enable_float.cmake)

find_package(emp-sh2pc REQUIRED)
include_directories(${EMP-SH2PC_INCLUDE_DIRS})

add_library(token-utils SHARED tokens/sha256.cpp tokens/hmac.cpp tokens/ecdsa.cpp tokens/tokens.cpp tokens/tokens-misc.cpp tokens/constants.cpp tokens/tx-builder.cpp tokens/test-e2e.cpp tokens/utils/ext-integer.hpp)
target_link_libraries(token-utils ${OPENSSL_LIBRARIES} ${GMP_LIBRARIES} ${EMP-OT_LIBRARIES})

add_executable(generate-circuit tokens/generate-circuit.cpp)
target_link_libraries(generate-circuit
        ${EMP-OT_LIBRARIES}
        ${GMP_LIBRARIES}
        token-utils)

install(TARGETS generate-circuit DESTINATION bin)

install(TARGETS token-utils DESTINATION lib)
set(TOKEN_HEADERS "tokens/tokens.h" "tokens/test-e2e.h" "tokens/ecdsa.h" "tokens/hmac.h" "tokens/sha256.h" "tokens/constants.h" "tokens/tokens-misc.h")
install(FILES ${TOKEN_HEADERS} DESTINATION include/update-state)

set(UTIL_HEADERS "tokens/utils/utils.h" "tokens/utils/utils.hpp" "tokens/utils/ext-integer.h" "tokens/utils/ext-integer.hpp")
install(FILES ${UTIL_HEADERS} DESTINATION include/update-state/utils)

set(IO_HEADERS "tokens/utils/io/gonet_io_channel.h" "tokens/utils/io/lndnet_io_channel.h" "tokens/utils/io/net_callback.h")
install(FILES ${IO_HEADERS} DESTINATION include/update-state/utils/io)


find_package(emp-ag2pc REQUIRED)
include_directories(${EMP-AG2PC_INCLUDE_DIRS})

install(FILES tokens/ag2pc/tokens.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/translation.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/test-e2e.h DESTINATION include/update-state/ag2pc)
install(FILES tokens/ag2pc/sha256.h DESTINATION include/update-state/ag2pc)

add_library(tokenm-utils SHARED tokens/ag2pc/tokens.cpp tokens/ag2pc/translation.cpp)
add_library(test-e2e SHARED tokens/ag2pc/test-e2e.cpp tokens/ag2pc/translation.cpp)
target_link_libraries(tokenm-utils ${EMP-OT_LIBRARIES}
        ${GMP_LIBRARIES})
target_link_libraries(test-e2e ${EMP-OT_LIBRARIES}
        ${GMP_LIBRARIES})

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
    ${GMP_LIBRARIES}
    ${EMP-OT_LIBRARIES}
    token-utils)
endmacro()

add_test(token-main)
add_test_ag2pc(tokens-main)
add_test_ag2pc(translation)
