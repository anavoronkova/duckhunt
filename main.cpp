#include "duckhunt.hpp"

std::vector<std::string> ref4b = create4b();
std::vector<std::string> ref4c = create4c();
std::vector<std::string> ref3a = create3a();
std::vector<std::string> ref4a = create4a();
std::vector<std::string> _1og = create1og();

std::vector<std::string> createErrorMessages() {
    std::vector<std::string> messages;
    messages.push_back("Your map is incorrect. Maybe try asking a duck for help next time?");
    messages.push_back("Duck hint: search intra to find the right map.");
    messages.push_back("Oops! That map doesn't seem to fit. Did you follow the duck's guidance?");
    messages.push_back("Incorrect map! Perhaps exploring the campus might reveal the answers you're looking for.");
    return messages;
}

std::string getRandomErrorMessage(const std::vector<std::string>& messages) {
    std::srand(std::time(0)); // Seed with the current time
    int index = std::rand() % messages.size();

    if (index % 2 == 0) {
        return MAGENTA + messages[index] + RESET;
    } else {
        return YELLOW + messages[index] + RESET;
    }
}

bool isMapMatch(const std::vector<std::string>& map, const std::vector<std::string>& reference) {
    if (map.size() != reference.size()) return false;
    for (size_t i = 0; i < map.size(); ++i) {
        if (map[i] != reference[i]) return false;
    }
    return true;
}

std::pair<const std::vector<std::string>*, std::pair<int, int> > findMatchingReference(const std::vector<std::string>& map) {
    if (isMapMatch(map, ref4b)) return std::make_pair(&ref4b, std::make_pair(4, 1)); // 5th row (index 4), position 1
    if (isMapMatch(map, ref4c)) return std::make_pair(&ref4c, std::make_pair(8, 8)); // 9th row (index 8), position 8
    if (isMapMatch(map, ref3a)) return std::make_pair(&ref3a, std::make_pair(10, 1)); // No specific highlight
    if (isMapMatch(map, ref4a)) return std::make_pair(&ref4a, std::make_pair(12, 10)); // No specific highlight
    if (isMapMatch(map, _1og)) return std::make_pair(&_1og, std::make_pair(19, 15)); // No specific highlight
    return std::make_pair(nullptr, std::make_pair(-1, -1));
}

void displayTreasure(const std::vector<std::string>& map, int highlightRow, int highlightCol) {
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if (i == highlightRow && j == highlightCol && map[i][j] == 'C') {
                std::cout << GREEN << 'C' << RESET;
            } else {
                std::cout << map[i][j];
            }
        }
        std::cout << "\n";
    }
}

int main(int ac, char *av[]) {
    if (ac < 2) {
        std::cerr << MAGENTA << "Error: No file provided. Usage: " << av[0] << " <filename>\n" << RESET;
        return 1;
    }

    std::ifstream file(av[1]);
    if (!file) {
        std::cerr << MAGENTA << "Error: Could not open the file: " << av[1] << "\n" << RESET;
        return 1;
    }

    std::vector<std::string> map;
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(line);
    }

    std::pair<const std::vector<std::string>*, std::pair<int, int> > result = findMatchingReference(map);
    const std::vector<std::string>* matchingReference = result.first;
    int highlightRow = result.second.first;
    int highlightCol = result.second.second;

    if (!matchingReference) {
        std::vector<std::string> errorMessages = createErrorMessages();
        std::cout << MAGENTA << getRandomErrorMessage(errorMessages) << "\n" << RESET;
        return 1;
    }
    
    displayTreasure(*matchingReference, highlightRow, highlightCol);

    return 0;
}