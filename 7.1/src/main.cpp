/*
 *  main.cpp
 *
 *  Date: Feb 13th 2022
 *  Author: Paul Mauviel
 */

#include <application.h>

int main(int argc, char** argv)
{

    Application app{std::filesystem::current_path() / "data" / "CS210_Project_Three_Input_File.txt"};
    app.Run();

}