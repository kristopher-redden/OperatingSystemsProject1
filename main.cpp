#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[])
{
    //http://www.cplusplus.com/reference/string/string/find_last_of/
    //Create directory one level lower.
    string exe = argv[0];
    size_t found = exe.find_last_of("/\\");
    string exeDirLocation = exe.substr(0,found);

    //Make an array to hold all values to send to g++.
    char **allFiles = new char *[200];
    string *destinationLocations = new string[200];

    allFiles[199] = nullptr;
    string gplusplus = "g++";
    allFiles[0] = const_cast<char *>(gplusplus.c_str());//ALT + Enter = ShortCut help.

    string fileNameToCopy;
    string src;
    string dst;
    //Copy the files to the new location.
    for (int fileNum = 1; fileNum < argc; fileNum++)
    {
        //Generate source file.
        src = argv[fileNum];
        boost::filesystem::path testFullPath(src);

        //Get filename.
        size_t found = src.find_last_of("/\\");
        fileNameToCopy = src.substr(found+1);

        //Check to see if the file is in the exe location or a full path.
        if (testFullPath.has_parent_path())
        {
            //Absolute path specified, file doesn't need folder path.
            boost::filesystem::path source(src);
            if (boost::filesystem::exists(source))
            {
                //Generate destination and copy.
                dst = "/var/tmp/" + fileNameToCopy;
                destinationLocations[fileNum] = const_cast<char *>(dst.c_str());
                boost::filesystem::path destination(dst);
                boost::filesystem::copy_file(source, destination,boost::filesystem::copy_option::overwrite_if_exists);
                allFiles[fileNum] = const_cast<char *>(destinationLocations[fileNum].c_str());

                if (boost::filesystem::exists(dst))
                    cout << "Copy of " + dst + " was successful." << endl ;
                else
                    cout << "Copy of " + dst + " failed." << endl;
            }
            else
            {
                string notFound = source.filename().c_str();
                cerr << notFound + " does not exist." << endl ;
            }
        }
        else
        {
            //Relative path specified, prepend exe location.
            string fileLocation = exeDirLocation + src;
            boost::filesystem::path source(src);

            if (boost::filesystem::exists(source))
            {
                //Generate destination and copy.
                dst = "/var/tmp/" + fileNameToCopy;
                destinationLocations[fileNum] = const_cast<char *>(dst.c_str());
                boost::filesystem::path destination(dst);
                boost::filesystem::copy_file(source, destination,boost::filesystem::copy_option::overwrite_if_exists);
                allFiles[fileNum] = const_cast<char *>(destinationLocations[fileNum].c_str());

                if (boost::filesystem::exists(dst))
                    cout << "Copy of " + dst + " was successful." << endl ;
                else
                    cout << "Copy of " + dst + " failed." << endl;
            }
            else
            {
                string notFound = source.filename().c_str();
                cerr << notFound + "does not exist" << endl ;
            }
        }
    }

    string outFileCommand = "-o";
    allFiles[argc] = const_cast<char *>(outFileCommand.c_str());
    string outputFileName = "/var/tmp/outputFileCompiled";
    allFiles[argc + 1] = const_cast<char *>(outputFileName.c_str());

    int childWait;
    pid_t pid = fork();
    if (pid == 0)
    {
        execv("/usr/bin/g++", allFiles);
    }
    else if (pid < 0)
    {
        cerr << "Failed to fork." << endl;
    }
    else
    {
        //Parent program, nothing to do.
    }

    waitpid(pid, &childWait, 0);
    if (boost::filesystem::exists(outputFileName))
    {
        cout << "Compilation successful." << endl;
    }
    else
    {
        cout << "Compilation failed." << endl;
    }
}