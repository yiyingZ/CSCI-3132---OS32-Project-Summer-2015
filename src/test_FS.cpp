#include <iostream>
#include "FileSystem.h"

using namespace std;

int main() {
    //build single instance of FileSystem for testing
    FileSystem& memory = FileSystem::getInstance();
    return 0;
}