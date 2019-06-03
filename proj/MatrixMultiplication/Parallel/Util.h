#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Defines.h"

using namespace std;

/**
* Cuvanje vremena i ubrzanja u fajlove
*/
void save_results(vector<double>& sts, vector<double>& pts, 
	vector<double>& speedup);

/**
* Otvaranje i citanje fajla
*/
void open_file(string file_name, ifstream& file);             

/**
* Ucitava matrice, stim sto matricu B ucitava transponovano 
*/
void load_matrices(ifstream& file, int** a, int** a1, int** b, int dim); 

/**
* Stampa matricu na ekran
*/
void print_matrix(int** m, int dim);

/**
* Kreira matircu datih dimenzija i upisuje je u zadati fajl
*/
void create_matrix(string file_name, int dim);                

/**
* kreira vise matrica za dimenzije zadate u gloalnom nizu DIMENSIONS 
*/
void create_matrices();										   

/**
* Zapisuje rezultat mnozenja u zadati fajl. 
*/
void write_matrix_to_file(string path, int** a, int dim);     

/**
* Serijsko mnozenje matrica
*/
void multiply_matrices_serial(int** a, int** b, int dim);
