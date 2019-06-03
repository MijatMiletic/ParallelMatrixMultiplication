#include "tbb/task.h"

using namespace tbb;

class MainTask : public task {
/*!
	Glavni zadatak koji kreira podzadatak 
	za mnozenje svakog reda iz matrice A
	sa svim kolonama matrice B.
*/

private:
	int dim;             
	int** a;
	int** b;
	task_list tasks;

public:
	MainTask(int** _a, int** _b, int _dim);
	task* execute();      
};