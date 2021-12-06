#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// function that reads the input file and returns a vector of strings
std::vector<std::string> read_input(std::string file_name)
{
    std::vector<std::string> input;
    std::string line;
    std::ifstream myfile(file_name);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            input.push_back(line);
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
    return input;
}

// parse input of commands and calculate final posiotion
int calculatePosition(std::vector<std::string> input)
{
    int x = 0;
    int y = 0;

    for (auto line : input)
    {

        ///
        std::string command = line.substr(0, line.find(" "));

        int steps = std::stoi(line.substr(line.find(" ") + 1));
        if (command == "forward")
        {
            x += steps;
        }
        else if (command == "down")
        {
            y += steps;
        }
        else if (command == "up")
        {
            y -= steps;
        }
    }

    return x*y;
}

// parse input of commands and calculate final posiotion
int  calculatePositionWithAim(std::vector<std::string> input)
{
    int x = 0;
    int y = 0;
    int aim = 0;

    for (auto line : input)
    {

        ///
        std::string command = line.substr(0, line.find(" "));

        int steps = std::stoi(line.substr(line.find(" ") + 1));
        if (command == "forward")
        {
            x += steps;
            y += aim * steps;
        }
        else if (command == "down")
        {
            aim += steps;
        }
        else if (command == "up")
        {
            aim -= steps;
        }
    }

    return x*y;
}
