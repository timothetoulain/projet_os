//g++ mvdir.cpp -o mvdir -lstdc++fs
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
 
int main(int argc, char** argv){
    fs::copy(argv[1], argv[2], fs::copy_options::recursive);
    fs::remove_all(argv[1]);

}