list(APPEND TEST_SRCS
    main.c
)

add_executable(${PROJECT_NAME}_test)
target_sources(${PROJECT_NAME}_test PRIVATE ${TEST_SRCS})

add_test(
    NAME ${PROJECT_NAME}_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${PROJECT_NAME}_test 
)


target_link_libraries(${PROJECT_NAME}_test
    PRIVATE IntelIPP::IntelIPP
)
