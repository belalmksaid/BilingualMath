
#include <iostream>
#include "math/math.h"
#include <vector>

using namespace std;

int main(int count, char* args[])
{
    if(count < 3) {
        cout << "Insufficient Inputs, Needs a [file_input] and [file_output]" << endl;
        return 0;
    }
    string file_input(args[1]), file_output(args[2]);
    // process file
    // render
    // save output
    // clean up
    return 0;
}