#ifndef PAL_HPP
#define PAL_HPP

#include <NFA.hpp>

#include <fstream>
#include <boost/algorithm/string.hpp>

NFA ReadNFA(std::string file_name);

std::vector<std::string> Split(std::string string, std::string separators);

bool IsStateFinal(const std::string& state_string);

#endif /* PAL_HPP */
