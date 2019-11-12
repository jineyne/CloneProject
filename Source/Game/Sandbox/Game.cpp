#include "Application.hpp"
#include "Debug/Debug.hpp"

using namespace cpf;

int main() {
    Debug::LogInfo("{}, {}", "Hello", "World");
    Debug::LogInfo("{1}, {0}", 1, "World");
    Debug::LogWarning("{}, {}", "This is", "Warning!");
    Debug::LogError("{}, {}", "Oh my GOD!", "Error!");
    Debug::LogFatal("{}, {}, {}", "Good norning", "Good afternoon", "Good evening");

    return 0;
}
