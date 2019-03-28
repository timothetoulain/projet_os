/*!
* \file cpdir.cpp
* \brief Copy directory
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to copy a directory : Command cpdir
*
*/
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
 
/*!
* \fn int main(int argc, char** argv)
* \brief Main program to copy a directory
* \param argc name of new directory
* \param argv destination file (not existing)
* \return int : 0 if cpdir done else return an error
*/
int main(int argc, char** argv){
    fs::copy(argv[1], argv[2], fs::copy_options::recursive);
}
