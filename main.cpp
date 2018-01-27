#include <iostream>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{
    //Copy files from one location to another.
    for (int paramCount = 1; paramCount < argc; paramCount++)
    {
        ifstream  src(argv[paramCount], ios::binary);
        //If the source file exists, then create a folder at the same level and copy it down.
        if (src.good())
        {
            path currentPath = current_path();
            string currentPathString = currentPath.string();
            string fileName = currentPath.filename().string();
            string newLocation = currentPathString + "/tempFolder";
            create_directories(newLocation);
            ofstream  dst(newLocation + fileName, ios::binary);
            dst << src.rdbuf();
        }
        else
        {
            string fileNotFound = argv[paramCount];
            cerr << fileNotFound + " file not found.";
        }
    }
//    //Open the file and get the data length of the extra frame's.
//    ifstream ifs (file1, ios::in | ios::binary);
//    int extraFrameCharLength = fileLength % 64;
//    if (ifs.good())
//    {
//        char character;
//        //We will have 67 chars in the frame, get the data for 2 - 65.
//        int fullFrames = fileLength / 64;
//        int extraFrameDataLength = fileLength % 64;
//        int allCharactersInFrame = fullFrames * 67 + extraFrameDataLength + 3;
//        int onlyDataCharacters = fullFrames * 64 + extraFrameDataLength;
//        unsigned char *chars = new unsigned char[onlyDataCharacters];
//        int charCount = 0;
//        while (ifs.get(character))
//        {
//            //Location 0 and 1 is SYN and ctrl, location 66 is the other SYN Char.
//            chars[charCount] = character;
//            charCount++;
//        }
//        dl.Framing(chars, file2, allCharactersInFrame, fullFrames, extraFrameDataLength, bitToFlip);
//        ifs.close();
//    }
//    else
//        throw 3;
}