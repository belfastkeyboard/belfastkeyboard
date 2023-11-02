/*
 *
 *      Wave Function Collapse Algorithm
 *      
 *      Algorithm I quickly wrote after watching a video on
 *      YouTube about it. Currently in a very basic state.
 * 
 * 
 *      Using:
 * 
 *          > Create an object of wave_function_collapse type
 *          and call the collapse.start() function. The function
 *          will create a graph and run through the process of 
 *          entropy decay.
 * 
 *          > The object will output the contents of each loop
 *          into a file called 'output.txt' in the .exe directory.
 * 
 *          > Size of the graph is governed by the ARRAY_SIZE pre-
 *          processor directive.
 * 
 *      ***          <---TO DO--->          ***
 * 
 *      Improve entropy system (certain values can only decay into other values).
 * 
 *      Write constructors.
 *          
 *          > Move away from C style array.
 *          > Not flexible enough.
 * 
 *      Improve error handling.
 * 
 *      Display graphics instead of .txt output.
 * 
 * 
 */

#ifndef     WAVE_FUNCTION_COLLAPSE
#define     WAVE_FUNCTION_COLLAPSE

#include    <fstream>
#include    <algorithm>

#include    "rng.hpp"

#define     ARRAY_SIZE      9

class wave_function_collapse
{
private:
    struct cell
    {
        int value;
        int x;
        int y;
    };
    cell array[ARRAY_SIZE][ARRAY_SIZE];
    cell lowest;
    cell highest;
    std::vector<cell> vec;

    Random& random = Random::instance();
    
    void reset()
    {
        vec.clear();
    }
    void createGraph()
    {
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            for (size_t j = 0; j < ARRAY_SIZE; j++)
            {
                array[i][j].value = 9; array[i][j].x = i; array[i][j].y = j;
            }
        }
        lowest.value = array[0][0].value; lowest.x = 0; lowest.y = 0;
        highest.value = array[0][0].value; highest.x = 0; highest.y = 0;
    }
    void findLowestEntropy()
    {
        int check = 10;
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            for (size_t j = 0; j < ARRAY_SIZE; j++)
            {
                if (array[i][j].value > check || array[i][j].value == 0) continue;
                if (array[i][j].value > 0 && array[i][j].value == check) {vec.push_back(array[i][j]); continue;}
                vec.clear(); vec.push_back(array[i][j]);
                check = array[i][j].value;
            }
        }
        if (vec.empty()) return;
        std::shuffle(vec.begin(), vec.end(), random.gen);
        lowest = vec.front();
    }
    void findHighestEntropy()
    {
        int check;
        check = array[0][0].value;
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            for (size_t j = 0; j < ARRAY_SIZE; j++)
            {
                if (array[i][j].value < check) continue;
                check = array[i][j].value;
            }
        }
        highest.value = check; 
    }
    void enactEntropy()
    {
        if (lowest.value < 1) return;
        array[lowest.x][lowest.y].value = random.number(0, array[lowest.x][lowest.y].value - 1);
        lowest.value = array[lowest.x][lowest.y].value;
    }
    void getNeighbours()
    {
        // up
        if (lowest.x > 0 && array[lowest.x - 1][lowest.y].value > 0)
                array[lowest.x - 1][lowest.y].value = random.number(lowest.value + 1, array[lowest.x - 1][lowest.y].value - 1);
        // down
        if (lowest.x < ARRAY_SIZE - 1 && array[lowest.x + 1][lowest.y].value > 0)
                array[lowest.x + 1][lowest.y].value = random.number(lowest.value + 1, array[lowest.x + 1][lowest.y].value - 1);
        // left
        if (lowest.y > 0 && array[lowest.x][lowest.y - 1].value > 0)
                array[lowest.x][lowest.y - 1].value = random.number(lowest.value + 1, array[lowest.x][lowest.y - 1].value - 1);
        // right
        if (lowest.y < ARRAY_SIZE - 1 && array[lowest.x][lowest.y + 1].value > 0)
                array[lowest.x][lowest.y + 1].value = random.number(lowest.value + 1, array[lowest.x][lowest.y + 1].value - 1);
    }
    void readGraph()
    {
        std::ofstream output("output.txt", std::ios::app);
        if (!output) return;
        for (size_t i = 0; i < ARRAY_SIZE; i++)
        {
            for (size_t j = 0; j < ARRAY_SIZE; j++)
            {
                output << array[i][j].value;
            }
            output << std::endl;
        }
        output << std::endl;
        output.close();
    }
public:
    void start()
    {
        createGraph();
        readGraph();
        while (highest.value > 0)
        {
            enactEntropy();
            getNeighbours();
            readGraph();
            reset();
            findLowestEntropy();
            findHighestEntropy();
        }
    }
};

#endif