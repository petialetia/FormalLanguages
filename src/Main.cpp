#include <DOA.hpp>
#include <PAL.hpp>
#include <NFA.hpp>
#include <MinimalDFA.hpp>

int main()
{
    auto nfa = ReadNFA("Example.pal");

    SaveInDOA(nfa, "Start.doa");

    ChangeToMinimalDFA(nfa);

    SaveInDOA(nfa, "Changed.doa");

    return 0;
}