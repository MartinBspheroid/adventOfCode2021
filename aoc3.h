#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

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

static int temp1 = 0;
static int temp2 = 0;
static int temp3 = 0;

int calculate(std::vector<std::string> input)
{
    const int lsize = input[0].size();
	std::bitset<32> gamma;
	std::bitset<32> epsilon;

    for (size_t i = 0; i < lsize; i++)
    {
        int zeroCount = 0;
        int oneCount = 0;
        for (size_t j = 0; j < input.size(); j++)

            input[j][i] == '1' ? oneCount++ : zeroCount++;

		oneCount > zeroCount ? gamma[lsize - 1 - i] = 1 : gamma[lsize - 1 - i] = 0;
		oneCount < zeroCount ? epsilon[lsize - 1 - i] = 1 : epsilon[lsize - 1 - i] = 0;
    }
    auto b1 = (unsigned long)gamma.to_ulong();
    auto b2 = (unsigned long)epsilon.to_ullong();
    return b1 * b2;
}