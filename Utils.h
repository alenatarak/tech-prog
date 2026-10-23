#pragma once
#include <iosfwd>
#include <string>

std::string readText(const std::string& label);
int readInt(const std::string& label, int minValue, int maxValue);
void writeString(std::ostream& out, const std::string& s);
std::string readString(std::istream& in);
void verifyStream(std::istream& in);
