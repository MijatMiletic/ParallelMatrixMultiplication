#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "test.h"
#include "util.h"
#include "Defines.h"

using namespace std;

int main(int argc, char** argv)
{
	/* First you will need to create control matrices 
	   a python script. */
	create_matrices();
	solve_all();
}






