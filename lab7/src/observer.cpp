#include "observer.h"

FileObserver::FileObserver(const std::string& filename) : filename(filename) {}

void FileObserver::Update(const std::string& message) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file from message: " << filename << std::endl;
    }
}

void ConsoleObserver::Update(const std::string& message) {
    std::cout << message << std::endl;
}