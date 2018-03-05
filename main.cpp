#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    //http://www.cplusplus.com/reference/string/string/find_last_of/
    //Create directory one level lower.
    string exeLocation = argv[0];
    size_t found = exeLocation.find_last_of("/\\");
    string locationToWriteNewFileTo = exeLocation.substr(0,found) + "/OperatingSystemProjectOneLevelLower/";
    boost::filesystem::create_directory(locationToWriteNewFileTo);

    string fileNameToCopy;
    string src;
    string dst;
    //Copy the files to the new location.
    for (int fileNum = 1; fileNum < argc; fileNum++)
    {
        src = argv[fileNum];
        boost::filesystem::path source(src);

        size_t found = src.find_last_of("/\\");
        fileNameToCopy = src.substr(found+1);

        dst = "/var/tmp/" + fileNameToCopy;//locationToWriteNewFileTo + fileNameToCopy;//"/var/tmp/" + fileNum;//
        boost::filesystem::path destination(dst);
        boost::filesystem::copy_file(source, destination,boost::filesystem::copy_option::overwrite_if_exists);
    }


//    if (boost::filesystem::create_directory(locationToWriteNewFileTo))
//    {
//        //Directory created successfully.
//        int x = 0;
//    }
//    else
//    {
//        //Directory creation failed.
//        int x = 0;
//    }
//    //Copy files from one location to another.
//    for (int paramCount = 1; paramCount < argc; paramCount++)
//    {
//        //http://www.cplusplus.com/forum/general/116829/
//        stringstream ss(argv[paramCount]);
//        string token;
//        while(getline(ss,token, '/'))
//        {
//            //Places what was split in the token.  What is left over is the filename.
//        }
//
//        //boost::filesystem::path thePath = boost::filesystem::current_path();
//
//        ifstream  src(argv[paramCount], ios::binary);
//        //If the source file exists, then create a folder at the same level and copy it down.
//        if (src.good())
//        {
//
//            string newLocation = locationToWriteNewFileTo + token;
//            ofstream  dst(newLocation, ios::binary);
//            dst << src.rdbuf();
//
//            ifstream check(newLocation, ios::binary);
//            if (check.good())
//            {
//                //It was copied successfully.
//                int x = 0;
//            }
//            else
//            {
//                //Not copied.
//                int x = 0;
//            }
//        }
//        else
//        {
//            string fileNotFound = argv[paramCount];
//            cerr << fileNotFound + " file not found.";
//            int x = 0;
//        }
//    }
}