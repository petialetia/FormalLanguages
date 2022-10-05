#include <DOA.hpp>
#include <MinimalCDFA.hpp>
#include <NFA.hpp>
#include <PAL.hpp>

int main() {
  auto nfa = ReadNFA("Example.pal");

  SaveInDOA(nfa, "Start.doa");

  ChangeToMinimalCDFA(nfa);

  SaveInDOA(nfa, "Changed.doa");

  return 0;
}