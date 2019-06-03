#include "Util.h"

using namespace std;

void open_file(string file_name, ifstream& file)
{
	file.open(file_name);

	if (!file){
		cerr << "Could not open file " << file_name << endl;
		exit(1);
	}
}

void load_matrices(ifstream &file, int **a, int** a1, int **b, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		a[i] = new int[dim];        
		b[i] = new int[dim]; 
		a1[i] = new int[dim];
		for (int j = 0; j < dim; j++)
		{									 
			file >> a[i][j]; 
			a1[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			file >> b[j][i];
		}
	}

	file.close();
}

void print_matrix(int **m, int dim)
{
	cout << "=====================" << endl;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << "=====================" << endl;
}

void create_matrices()
{
	for (int dim : DIMENSIONS) {
		string file_name = INPUT_PATH
			+ to_string(dim) + ".txt";
		create_matrix(file_name, dim);
	}
}

void create_matrix(string file_name, int dim)
{
	ofstream ofs;
	ofs.open(file_name);

	if (!ofs) {                            /* Provera fajla */
		cerr << "Cannot open file " << file_name <<
			" for creating a matrix " << endl;
		exit(1);
	}

	cout << "Creatig matrix: " << dim << "x" << dim << " ..." << endl;
	ofs << dim << endl;                     /* Zapisivanje dimenzije */
	for (int i = 0; i < dim; i++)           /* Zapisivanje matrice A */
	{
		for (int j = 0; j < dim; j++)
		{
			ofs << j << endl;
		}
	}
	cout << "Done creating matrix A." << endl;

	for (int i = 0; i < dim; i++)             /* Zapisivanje matrice B */
	{
		for (int j = 0; j < dim; j++)
		{
			ofs << j << endl;
		}
	}
	cout << "Done creating matrix B." << endl;
	ofs.close();
}


void write_matrix_to_file(string path, int** a, int dim)
{
	ofstream f;
	f.open(path);

	if (!f) {
		cerr << "Cannot open file " << path << endl;
		exit(1);
	}

	f << dim << endl;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			f << a[i][j] << endl;
		}
	}

	f.close();
}

void save_results(vector<double>& sts, vector<double>& pts,
	vector<double>& speedup)
{
	ofstream f_speedup(SPEEDUP_PATH);
	ofstream f_parallel(PARALLEL_TIME_PATH);
	ofstream f_serial(SERIAL_TIME_PATH);

	cout << "Saving speed up time results to file " << SPEEDUP_PATH << endl;
	cout << "Saving parallel time results to file " << PARALLEL_TIME_PATH << endl;
	cout << "Saving serial time results to file " << SERIAL_TIME_PATH << endl;

	for (int dim : DIMENSIONS) {
		f_speedup << dim << " " << speedup.front() << endl;
		speedup.erase(speedup.begin());

		f_parallel << dim << " " << pts.front() << endl;
		pts.erase(pts.begin());

		f_serial << dim << " " << sts.front() << endl;
		sts.erase(sts.begin());
	}
}

void multiply_matrices_serial(int** a, int** b, int dim)
{
	int* temp = new int[dim];						/* bafer */
	for (int i = 0; i < dim; i++) {
		for (int t = 0; t < dim; t++) {				/* inicijalizacija bafera */
			temp[t] = 0;
		}

		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				temp[j] += a[i][k] * b[j][k];
			}
		}
		for (int t = 0; t < dim; t++) {				/* parznjenje bafera */
			a[i][t] = temp[t];
		}
	}

	delete[] temp;
}