#include "stdafx.h"
#include "matrix.h"


matrix::matrix(const int _n) {
	n = _n;
	data = new float*[n];
	for (int i = 0; i < n; i++)
	{
		data[i] = new float[n];
		for (int j = 0; j < n; j++)
		{
			data[i][j] = 0;
		}
	}
}

inline bool space(char c) {
	return std::isspace(c);
}

inline bool notspace(char c) {
	return !std::isspace(c);
}

//break a sentence into words
std::vector<std::string> split(const std::string& s) {
	typedef std::string::const_iterator iter;
	std::vector<std::string> ret;
	iter i = s.begin();
	while (i != s.end()) {
		i = std::find_if(i, s.end(), notspace); // find the beginning of a word
		iter j = std::find_if(i, s.end(), space); // find the end of the same word
		if (i != s.end()) {
			ret.push_back(std::string(i, j)); //insert the word into vector
			i = j; // repeat 1,2,3 on the rest of the line.
		}
	}
	return ret;
}


void matrix::toOneDiagonalMatrix()
{

#ifdef PARALLEL 
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[i][j] = data[i][j] / data[i][i];
		}
	}
#else
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data[i][j] = data[i][j] / data[i][i];
		}
	}
#endif // PARALLEL 
}

void matrix::swapRows(int index) {
	for (int i = index + 1; i < n; i++)
	{
		if (data[i][index] != 0)
		{
			float* tmp = data[i];
			data[i] = data[index];
			data[index] = tmp;
			return;
		}
	}

	throw new exception("детерминант == 0");
}

void matrix::rowSubstractionForTriangle(int index) {
	if (data[index][index] == 0)
	{
		swapRows(index);
	}
	for (int i = index + 1; i < n; i++)
	{
		if (data[i][index] != 0) {
			float multiplier = data[i][index];
			for (int j = 0; j < n; j++)
			{
				data[i][j] -= (data[index][j] * multiplier) / data[index][index];
			}
			cout << endl;
		}
	}
}

void matrix::toTriangleMatrix()
{
	for (int i = 0; i < n - 1; i++)
	{
		rowSubstractionForTriangle(i);
	}
}

void matrix::rowSubstractionForTriangleParallel(int index)
{
	if (data[index][index] == 0)
	{
		swapRows(index);
	}

#pragma omp parallel for schedule(dynamic)
	for (int i = index + 1; i < n; i++)
	{
		if (data[i][index] != 0) {
			float multiplier = data[i][index];
			for (int j = 0; j < n; j++)
			{
				data[i][j] -= (data[index][j] * multiplier) / data[index][index];
			}
			cout << endl;
		}
	}
}

void matrix::toTriangleMatrixParallel()
{
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < n - 1; i++)
	{
		rowSubstractionForTriangle(i);
	}
}

float matrix::getMultiplyDiagonalElements() {
	float sum = 1;
	for (int i = 0; i < n; i++)
	{
		sum *= data[i][i];
	}

	return sum;
}


float matrix::getDeterminant()
{
	//toOneDiagonalMatrix();
	toTriangleMatrix();
	return getMultiplyDiagonalElements();
}

float matrix::getDeterminantParallel()
{
	toTriangleMatrixParallel();
	return getMultiplyDiagonalElements();
}

matrix matrix::parse(char* filename)
{
	matrix* m = new matrix(0);
	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		int state = 0, j = 0, numNotNull = 0, numStr = 0;
		while (getline(myfile, line)) {
			switch (state)
			{
			case 0:
				delete(m);
				m = new matrix((int)atol(line.c_str()));
				state++;
				break;
			case 1:
				numNotNull = (int)atol(line.c_str());
				state++;
				break;
			case 2:
				if (numNotNull == 0)
				{
					numNotNull = (int)atol(line.c_str());
					numStr++;
				}
				else
				{
					numNotNull--;
					std::vector<std::string> spt = split(line);
					int index = (int)atol(spt[0].c_str()),
						value = (int)atol(spt[1].c_str());

					m->data[numStr][index - 1] = value;
				}
				break;
			default:
				break;
			}
		}

	}

	return *m;
}

void matrix::print() {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << " " << data[i][j] << " ; ";
		}
		cout << endl;
	}
}

void matrix::printFile() {
	ofstream myfile;
	string name = "ouput" + to_string(rand() % 10 + 1);
	name += ".csv";
	myfile.open(name.c_str());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			myfile << data[i][j] << ";";
		}
		myfile << endl;
	}
	myfile.close();
}

matrix::~matrix()
{
	for (int i = 0; i < n; i++)
	{
		delete(data[i]);
	}

	delete[] (data);
}
