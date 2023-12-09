#include <iostream>
#include <string>

void exampleFunction(const std::string& name) {
    // Convert const string& to string
    std::string nameCopy(name);

    // Now, nameCopy is a regular (non-constant) std::string
    std::cout << "Copied string: " << nameCopy << std::endl;
}

int main() {
    std::string originalString = "https://www.prothomalo.com/";
    exampleFunction(originalString);

    return 0;
}
