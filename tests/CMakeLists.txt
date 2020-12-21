message(STATUS "COMPILING AND RUNNING TESTS")

# test utils
add_executable(test_utils test_utils.cpp)
target_link_libraries(test_utils pcv)

# test logging and timer functionalities
add_executable(test_logger test_logger.cpp)
target_link_libraries(test_logger pcv)

# test event creation and hook up
add_executable(test_event test_event.cpp)
target_link_libraries(test_event pcv)

# test window creation
add_executable(test_window test_window.cpp)
target_link_libraries(test_window pcv)
