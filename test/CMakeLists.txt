find_package(GTest)
find_package(Threads)

add_executable(Tests EXCLUDE_FROM_ALL MainTests.cpp NFATests.cpp EpsilonTransitionsRemovingTests.cpp SingleLetterTransitionsTests.cpp CDFATests.cpp MinimalCDFATests.cpp)
target_link_libraries(Tests PUBLIC ${GTEST_LIBRARIES} Threads::Threads NFA EpsilonTransitionsRemoving SingleLetterTransitions CDFA MinimalCDFA)

target_code_coverage(Tests AUTO EXCLUDE test/*)