#include "MainTask.h"
#include "RowAndAllCols.h"

MainTask::MainTask(int** _a, int** _b, int _dim) :
	a(_a),
	b(_b),
	dim(_dim)
{}

task* MainTask::execute()
{
	for (int i = 0; i < dim; i++) {                 // za svaki red u matrici A
		tasks.push_back(*new(allocate_child())      // napravi task koji mnozi 
			RowAndAllCols(a, b, i, dim));           // taj red sa svim kolonama 
	}                                               // iz matrice B
	set_ref_count(dim + 1);
	spawn_and_wait_for_all(tasks);
	return NULL;
}