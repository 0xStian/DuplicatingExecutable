#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <experimental/filesystem>
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
using namespace std;
namespace fs = std::experimental::filesystem;
string OriginalfileName = "dupe.exe";
string InfectedfileName = "infected.exe";
string Directory = "infected";
bool alreadyInfected();

bool checkFile(const std::string& InfectedfileName) {
    if (FILE* file = fopen(InfectedfileName.c_str(), "r")) {
        fclose(file);
        return true;
    }else {
        return false;
    }
}

bool alreadyInfected() {
    if (checkFile(Directory + "\\" + InfectedfileName) == true) {
        return true;
    }else if (fs::is_directory(Directory) || fs::exists(Directory)) {
        return true;
    }else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    //checks if the file and folder already exist
    if (alreadyInfected() == false) {
        //create directory
        fs::create_directory(Directory);
        //copy exe to new destination
        std::ifstream src(OriginalfileName, std::ios::binary);
        std::ofstream dst(Directory + "\\" + InfectedfileName, std::ios::binary);
        dst << src.rdbuf();
    }
    else {
        return 0;
    }
}
