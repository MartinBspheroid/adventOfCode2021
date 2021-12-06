#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <functional>
#include <algorithm>

/*

--- Day 4: Giant Squid ---
You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7
After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?

To begin, get your puzzle input.
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
using namespace std;

// split string to vector of number separated by character delimiter
std::vector<int> split_string(std::string str, char delimiter)
{
    std::vector<int> result;
    std::stringstream ss(str);
    std::string item;
    while (getline(ss, item, delimiter))
    {
        if (item != "")
            result.push_back(stoi(item));
    }
    return result;
}

typedef vector<vector<int>> Grid;
struct Board
{
    Grid grid;
    bool won = false;
};

int calculateBingo(vector<string> input)
{

    // first line of input are drawn numbers, as string separated by commas
    vector<int> drawnNumbers = split_string(input[0], ',');

    // rest are boards with numbers, separated by empty lines

    // separate boards from input into vector of vectors

    vector<Board> boards;
    Board t_board;
    for (int i = 2; i < input.size(); i++)
    {
        if (input[i] == "")
        {
            boards.push_back(t_board);
            t_board = Board();
        }
        else
        {
            t_board.grid.push_back(split_string(input[i], ' '));
        }
    }
    boards.push_back(t_board);
    // now we have all the boards and the drawn numbers
    // we need to find first board that wins
    // we need to find the first board that has all numbers in a row or column

    bool stop = false;
    int boardIndex = 0;
    int winningBoardIndex = 0;
    int round = 0;
    while (!stop)

    {
        int number = drawnNumbers[round];
        // draw number, find it if it is on board and mark it on the board by setting it to -1
        // iterate through all boards using for auto

        for (auto &board : boards)
        {
            for (auto &row : board.grid)
            {
                for (auto &num : row)
                {
                    if (num == number)
                    {
                        num = -1;
                    }
                }
            }
        }

        // check if any board has all numbers in a row or column
        int boardIndex = 0;
        for (auto &board : boards)
        {

            bool row = false;
            bool column = false;
            for (int j = 0; j < board.grid.size(); j++)
            {
                if (std::all_of(board.grid[j].begin(), board.grid[j].end(), [&](int i)
                                { return i == -1; }))
                {
                    row = true;
                }
            }
            for (int row = 0; row < board.grid.size(); row++)
            {
                // sum or each column is negative of number of number of rows
                int sum = 0;
                for (int k = 0; k < board.grid[row].size(); k++)
                {
                    sum += board.grid[row][k];
                }
                if (sum == -board.grid.size())
                {
                    column = true;
                }
            }
            if (row || column)
            {
                winningBoardIndex = boardIndex;
                Board wb = boards[winningBoardIndex];
                int sum = 0;
                for (auto &_row : wb.grid)
                {

                    for (auto &n : _row)
                    {
                        if (n != -1)
                        {
                            sum += n;
                        }
                    }
                }
                return sum * number;
            }
            boardIndex++;
        }

        round++;
    }
}

int calculateBingoLast(vector<string> input)
{

    // first line of input are drawn numbers, as string separated by commas
    vector<int> drawnNumbers = split_string(input[0], ',');

    // rest are boards with numbers, separated by empty lines

    // separate boards from input into vector of vectors

    vector<Board> boards;
    Board t_board;
    for (int i = 2; i < input.size(); i++)
    {
        if (input[i] == "")
        {
            boards.push_back(t_board);
            t_board = Board();
        }
        else
        {
            t_board.grid.push_back(split_string(input[i], ' '));
        }
    }
    boards.push_back(t_board);
    // now we have all the boards and the drawn numbers
    // we need to find first board that wins
    // we need to find the first board that has all numbers in a row or column

    bool stop = false;
    
    int round = 0;
    while (!stop)

    {
        int number = drawnNumbers[round];
        // draw number, find it if it is on board and mark it on the board by setting it to -1
        // iterate through all boards using for auto

        for (auto &board : boards)
        {
            for (auto &row : board.grid)
            {
                for (auto &num : row)
                {
                    if (num == number)
                    {
                        num = -1;
                    }
                }
            }
        }

        // check if any board has all numbers in a row or column
        int boardIndex = 0;

        for (auto &board : boards)
        {

            bool row = false;
            bool column = false;
            for (int j = 0; j < board.grid.size(); j++)
            {
                if (std::all_of(board.grid[j].begin(), board.grid[j].end(), [&](int i)
                                { return i == -1; }))
                {
                    row = true;
                }
            }
            for (int row = 0; row < board.grid.size(); row++)
            {
                // sum or each column is negative of number of number of rows
                int sum = 0;
                for (int k = 0; k < board.grid[row].size(); k++)
                {
                    if (board.grid[row][k] == -1) {
                        sum++;
                    }
                }
                if (sum == board.grid.size())
                {
                    column = true;
                }
            }
            if (row || column)
            {
                if (boards.size() == 1)
                {

                    Board wb = boards[boardIndex];
                    int sum = 0;
                    for (auto &_row : wb.grid)
                    {

                        for (auto &n : _row)
                        {
                            if (n != -1)
                            {
                                sum += n;
                            }
                        }
                    }
                    return sum * number;
                }
                else
                {
                    board.won = true;
                }
            }

            boardIndex++;
        }
        /// remove boards that won
        if (boards.size() < 10) {
            int sdf; 
        }
        boards.erase(std::remove_if(boards.begin(), boards.end(),
                                    [](Board &b)
            { return b.won; }),
                     boards.end());
        round++;
        if (boards.size() == 0) {
            stop = true;
        }
    }
    return -1;
}