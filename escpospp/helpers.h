#pragma once
#ifndef INCLUDE_HELPERS
#define INCLUDE_HELPERS

#include <string>
#include <vector>

namespace EscPos {

// Function to load an image file into the required format for the printer
std::vector<std::vector<bool>> loadImage(const std::string &filename);

} // namespace EscPos

#endif // INCLUDE_HELPERS
