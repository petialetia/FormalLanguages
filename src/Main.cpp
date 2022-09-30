#include <DOA.hpp>
#include <PAL.hpp>
#include <NFA.hpp>
#include <MinimalCDFA.hpp>

int main()
{
    auto nfa = ReadNFA("Example.pal");

    SaveInDOA(nfa, "Start.doa");

    ChangeToMinimalCDFA(nfa);

    SaveInDOA(nfa, "Changed.doa");

    return 0;
}