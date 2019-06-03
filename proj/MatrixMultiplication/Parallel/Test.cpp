#include <iostream>
#include <fstream>

#include "Defines.h"
#include "test.h"
#include "MainTask.h"
#include "Util.h"
#include "tbb/tick_count.h"
#include "tbb/task.h"

using namespace std;


void solve_all()
{
	vector<double> serial_time;
	vector<double> parallel_time;
	vector<double> speed_up;
	for (int dim : DIMENSIONS) {
		string in_file_name = INPUT_PATH + to_string(dim) + ".txt";
		string out_file_name = OUTPUT_PATH + to_string(dim) + ".txt";
		solve(in_file_name, out_file_name, serial_time, parallel_time, speed_up);
	}

	save_results(serial_time, parallel_time, speed_up);
}

void solve(string input_path, string output_path, vector<double>& sts,
	vector<double>& pts, vector<double>& speedup)
{
	// otvaranje fajla i citanje dimenzija
	ifstream file;
	open_file(input_path, file);
	int dim;
	file >> dim;
	int** a = new int *[dim];        /* dvodimenzionalan niz intova */
	int** b = new int *[dim];
	int** a1 = new int *[dim];        /* za serijsko mnozenje */

	// ucitavanje matrica u program
	cout << "1. Loading matrices from file: " <<
		input_path << ". dimension: " <<
		dim << " ..." << endl;
	load_matrices(file, a, a1, b, dim);
	cout << "--  Loading finished." << endl;

	// paralelno mnozenje matrica
	cout << "2. Multiplying matrices with parallel function ..." << endl;
	tick_count start_parallel = tick_count::now();
	MainTask& t = *new(task::allocate_root()) MainTask(a, b, dim);
	task::spawn_root_and_wait(t);
	tick_count end_parallel = tick_count::now();
	auto parallel_time = (end_parallel - start_parallel).seconds();
	cout << "--  Task finished, it took: " <<
		parallel_time << "s." << endl;
	pts.push_back(parallel_time);

	// poredjenje paralelnog rezultata 
	cout << "3. Comparing test matrix with control matrix..." << endl;
	string path = CONTROL_INPUT_PATH + to_string(dim) + ".txt";
	if (compare_files(path, a, dim)) {
		cout << "--  Result matrix is valid" << endl;
	}
	else {
		cout << "--  Result matrix is invalid" << endl << endl << endl;
	}

	// serijsko mnozenje
	cout << "4. Multiplying matrices with serial function ..." << endl;
	tick_count start_serial = tick_count::now();
	multiply_matrices_serial(a1, b, dim);
	tick_count end_serial = tick_count::now();
	auto serial_time = (end_serial - start_serial).seconds();
	cout << "--  Task finished, it took: " <<
		serial_time << "s." << endl;
	sts.push_back(serial_time);


	// poredjenje serijskog rezultata 
	cout << "5. Comparing test matrix with control matrix ..." << endl;
	if (compare_files(path, a, dim)) {
		cout << "--  Result matrix is valid." << endl;
	}
	else {
		cout << "--  Result matrix is invalid." << endl << endl << endl;
	}

	// ubrzanje
	double accs = serial_time / parallel_time;
	cout << "--  Parallel is " << accs << 
		" times faster than serial." << endl;
	speedup.push_back(accs);

	/* pisanje matrice u fajl
	cout << "6. Writing matrix to file " << 
		out_file_name << " ..." << endl;
	write_matrix_to_file(out_file_name, a, dim);
	*/

	cout << "--  Finished." << endl << endl;

	}

bool compare_files(string python_txt_file, int** test_matrix, int dim_t)
{
	ifstream control_file(python_txt_file);
	if (!control_file) {
		cerr << "Cannot open file " << python_txt_file << " for comparing." << endl;
		exit(1);
	}
	// ucitavanje i provera dimenzija
	int dim_c;
	control_file >> dim_c;
	if (dim_c != dim_t) {
		cout << "Dimensions are different." << endl;
		return false;
	}


	// poredjenje
	int a; // element iz kontrolne matrice 
	for (int i = 0; i < dim_c; i++) {
		for (int j = 0; j < dim_c; j++) {
			control_file >> a;
			if (a != test_matrix[i][j]) { 
				control_file.close();
				return false;
			}
		}
	}

	control_file.close();
	return true;
}

