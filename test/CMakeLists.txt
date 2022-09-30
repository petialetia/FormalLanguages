find_package(GTest)
find_package(Threads)

add_executable(Tests EXCLUDE_FROM_ALL MainTests.cpp NFATests.cpp EpsilonTransitionsRemovingTests.cpp SingleLetterTransitionsTests.cpp DFATests.cpp MinimalDFATests.cpp)
target_link_libraries(Tests PUBLIC ${GTEST_LIBRARIES} Threads::Threads NFA EpsilonTransitionsRemoving SingleLetterTransitions DFA MinimalDFA)

target_code_coverage(Tests AUTO EXCLUDE test/*)