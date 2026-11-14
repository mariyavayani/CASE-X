#ifndef UI_H
#define UI_H

#include <iostream>
#include <sstream>
#include <string>

const int BOX_WIDTH = 46;

// One line of a box, padded so the right edge lines up
inline void boxLine(const std::string& text) {
    int pad = BOX_WIDTH - (int)text.size();
    if (pad < 0) pad = 0;
    std::cout << "  |" << text << std::string(pad, ' ') << "|\n";
}

inline void boxEdge(char c) {
    std::cout << "  +" << std::string(BOX_WIDTH, c) << "+\n";
}

inline void showBanner() {
    std::cout << "\n";
    boxEdge('=');
    boxLine("");
    boxLine("    C A S E - X");
    boxLine("    Crime Scene Investigation Simulator");
    boxLine("");
    boxLine("    CASE FILE No. 001");
    boxLine("    The Qureshi Residence Incident");
    boxLine("");
    boxEdge('=');
}

inline void showMenu() {
    std::cout << "\n";
    boxEdge('-');
    boxLine("  INVESTIGATION MENU");
    boxEdge('-');
    boxLine("  1. Examine the crime scene");
    boxLine("  2. Evidence locker: look up an exhibit");
    boxLine("  3. Lab queue: analyze next evidence");
    boxLine("  4. Undo last analysis");
    boxLine("  5. Timeline board");
    boxLine("  6. Suspect register: look up a suspect");
    boxLine("  7. Case board: suspect ranking");
    boxLine("  0. Close the case");
    boxEdge('-');
}

inline void printHeader(const std::string& title) {
    std::cout << "\n  ---[ " << title << " ]---\n\n";
}

inline void waitForEnter() {
    std::cout << "\n  Press Enter to continue...";
    std::string s;
    std::getline(std::cin, s);
}

// Keeps asking until the user types a whole number
inline int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) return 0;   // input closed: act like exit
        std::stringstream ss(line);
        int n;
        char extra;
        if (ss >> n && !(ss >> extra)) return n;
        std::cout << "  Please type a number.\n";
    }
}

// Floor plan matching the graph: Entrance, Hall, Living Room, Kitchen, Bedroom, Study
inline void showFloorPlan() {
    std::cout << "  +-----------+              +-----------+\n"
              << "  |  BEDROOM  |              | [X] STUDY |\n"
              << "  +-----+-----+              +-----+-----+\n"
              << "        |                          |\n"
              << "        +------------+-------------+\n"
              << "                     |\n"
              << "               +-----+-----+\n"
              << "               |   HALL    |\n"
              << "               +--+-----+--+\n"
              << "                  |     |\n"
              << "        +---------+     +----------+\n"
              << "        |                          |\n"
              << "  +-----+-----+             +------+------+\n"
              << "  |  ENTRANCE |             | LIVING ROOM |\n"
              << "  +-----+-----+             +------+------+\n"
              << "        |                          |\n"
              << "        |      +-----------+       |\n"
              << "        +------+  KITCHEN  +-------+\n"
              << "               +-----------+\n\n"
              << "  [X] = crime scene     Front door: Entrance     Back door: Kitchen\n";
}

#endif