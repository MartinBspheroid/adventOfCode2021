#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <functional>
#include <algorithm>

/*
Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
If you only have one number left, stop; this is the rating value for which you are searching.
Otherwise, repeat the process, considering the next bit to the right.
The bit criteria depends on which type of rating value you want to find:

To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
Then, to determine the CO2 scrubber rating value from the same example above:

Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)
*/

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
int calculate(std::vector<std::string> input)
{
    const int lsize = input[0].size();
    std::bitset<32> gamma, epsilon;

    for (size_t i = 0; i < lsize; i++)
    {
        int zeroCount = 0;
        int oneCount = 0;
        for (size_t j = 0; j < input.size(); j++)
            input[j][i] == '1' ? oneCount++ : zeroCount++;
        oneCount > zeroCount ? gamma[lsize - 1 - i] = 1 : gamma[lsize - 1 - i] = 0;
        oneCount < zeroCount ? epsilon[lsize - 1 - i] = 1 : epsilon[lsize - 1 - i] = 0;
    }
    return epsilon.to_ullong() * gamma.to_ulong();
}

bool getMostCommonValuesAtIndex(std::vector<std::string> &input, int index)
{
    std::pair<int, int> result;
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i][index] == '1')
            result.first++;
        else
            result.second++;
    }
    return result.first > result.second || result.first == result.second;
}

int getLifeSupport(std::vector<std::string> input)
{
    const int lsize = input[0].size();
    // convert line to vector of bits
    std::vector<std::string> base;
    for (auto line : input)
        base.push_back((line));
    //--

    // function that take x elements from beginning of vector that matches the condition test bool
    auto take_x_elements_from_beginning = [&](std::vector<std::string> &set, int index, char test)
    {
        std::vector<std::string> result;
        for (size_t i = 0; i < set.size(); i++)
        {
            if (set[i][index] == test)
                result.push_back(set[i]);
        }
        return result;
    };

    int index = 0;
    // keep on removing until there is only one element left
    auto o2bits = base;

    // find oxygen generator rating
    while (o2bits.size() > 1)
    {
        // get the most common value at index
        auto most_common_value = getMostCommonValuesAtIndex(o2bits, index);
        // if most common value is 1, keep only elements with 1 at index
        if (most_common_value)
            o2bits = take_x_elements_from_beginning(o2bits,  index, '1');
        // if most common value is 0, keep only elements with 0 at index
        else
            o2bits = take_x_elements_from_beginning(o2bits,  index, '0');
        index++;
    }
    // find CO2 scrubber rating
    index = 0;
    auto c2bits = base;

    while (c2bits.size() > 1)
    {
        auto most_common_value = getMostCommonValuesAtIndex(c2bits, index);
        if (most_common_value)
        {
            c2bits = take_x_elements_from_beginning(c2bits, index, '0');
        }
        else
        {
            c2bits = take_x_elements_from_beginning(c2bits, index, '1');
        }
        index++;
    }
    // multiply oxygen generator rating and CO2 scrubber rating

    // convert bits to int
    int o2 = std::stoi(o2bits[0], nullptr, 2);
    int c2 = std::stoi(c2bits[0], nullptr, 2);
    return o2 * c2;
}