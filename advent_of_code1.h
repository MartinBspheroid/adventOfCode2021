#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>

//function that checks if file exists and reads file and returns vector of ints
std::vector<int> readValues(std::string file_name)
{
    std::vector<int> file_contents;
    std::ifstream file(file_name);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            file_contents.push_back(std::stoi(line));
        }
        file.close();
    }
    else
    {
        std::cout << "File not found" << std::endl;
    }
    return file_contents;
}

int calculateSonarDifferences(std::vector<int> &input)
{
    int differences = 0;

    for (int i = 1; i < input.size(); i++)
    {
        input[i] > input[i - 1] ? differences++ : differences;
    }
    return differences;
}

int calculateSonarDifferencesAlgo(std::vector<int> &input)
{
    int index = 0;
    return std::count_if(input.begin() + 1, input.end(), [&index, &input](int element)
                         { return element > input[index++]; });
}

int calculateSonarDifferencesWithWindow(std::vector<int> &input)
{
    std::vector<int> windows;
    //calculate windows
    for (int i = 2; i < input.size(); i++)
    {
        windows.push_back(input[i] + input[i - 1] + input[i - 2]);
    }
    int differences = 0;
    //compare windows
    for (int i = 1; i < windows.size(); i++)
    {
        windows[i] > windows[i - 1] ? differences++ : differences;
    }
    return differences;
}

int calculateSonarDifferencesWithWindowsAlgo(std::vector<int> &input)
{
    int index = 0;
    auto it = input.begin();
    return std::count_if(input.begin(), input.end() - 3, [&index, &input, it](int element)
                         {
                             bool result = std::accumulate(it + index, it + (index + 3), 0) < std::accumulate(it + index + 1, it + (index + 4), 0);
                             index++;
                             return result;
                         });
}