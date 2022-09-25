find_package(GTest)
find_package(Threads)

add_executable(Tests EXCLUDE_FROM_ALL MainTests.cpp EpsilonTransitionsRemovingTests.cpp)
target_link_libraries(Tests PUBLIC ${GTEST_LIBRARIES} Threads::Threads NFA EpsilonTransitionsRemoving)