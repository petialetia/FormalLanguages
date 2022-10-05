add_library(NFA STATIC NFA.cpp)
add_library(DOA STATIC DOA.cpp)
add_library(PAL STATIC PAL.cpp)
add_library(EpsilonTransitionsRemoving STATIC EpsilonTransitionsRemoving.cpp)
add_library(SingleLetterTransitions STATIC SingleLetterTransitions.cpp)

add_library(CDFA STATIC CDFA.cpp)
target_link_libraries(CDFA EpsilonTransitionsRemoving SingleLetterTransitions)

add_library(MinimalCDFA MinimalCDFA.cpp)
target_link_libraries(MinimalCDFA NFA CDFA)

add_executable(Main Main.cpp)
target_link_libraries(Main DOA MinimalCDFA PAL)