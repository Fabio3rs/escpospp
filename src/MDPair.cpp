#include <escpospp/EscPosCommands.h>
#include <escpospp/MDPair.h>
#include <utility>

std::map<std::string, MDPair *> MDPair::mdPairMap =
    std::map<std::string, MDPair *>();

MDPair::MDPair(std::string id) : id_(std::move(id)) {
    // Empty constructor
}

MDPair MDPair::getMatching(const std::string &toMatch) {
    // Check if we need to initialize the map
    if (mdPairMap.empty()) {
        initializeMap();
    }

    auto result = mdPairMap.find(toMatch);
    if (result == mdPairMap.end()) {
        throw -1;
    }
    return *result->second;
}

void MDPair::initializeMap() {
    // First we load the underline font thingy
    mdPairMap["__"] = new MDPair("__");
    mdPairMap["__"]->first = EscPos::UNDERLINE_2_DOT;
    mdPairMap["__"]->second = EscPos::UNDERLINE_OFF;

    mdPairMap["**"] = new MDPair("**");
    mdPairMap["**"]->first = EscPos::BOLD_ON;
    mdPairMap["**"]->second = EscPos::BOLD_OFF;
}
