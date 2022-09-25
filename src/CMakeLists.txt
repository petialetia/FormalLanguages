add_library(NFA STATIC NFA.cpp)
add_library(DOA STATIC DOA.cpp)
add_library(EpsilonTransitionsRemoving STATIC EpsilonTransitionsRemoving.cpp)
add_library(SingleLetterTransitions STATIC SingleLetterTransitions.cpp)

add_executable(MinimalDFA MinimalDFA.cpp)
target_link_libraries(MinimalDFA NFA DOA EpsilonTransitionsRemoving SingleLetterTransitions)