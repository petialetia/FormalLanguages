#ifndef DOA_HPP
#define DOA_HPP

#include "NFA.hpp"

void SaveInDOA(const NFA& nfa, std::string file_name = "NFA.doa");
void WriteAcceptance(const NFA& nfa, std::ofstream& doa_file);
void WriteStates(const NFA& nfa, std::ofstream& doa_file);

#endif /* DOA_HPP */
