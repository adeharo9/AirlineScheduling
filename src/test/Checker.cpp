#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

typedef unsigned int uint;

void read(const string& filePath, vector<string>& names, vector<uint>& values)
{
	ifstream file;

	file.open(filePath, fstream::in);

	string auxString;
	uint auxUint;

	while(file >> auxString)
	{
		file >> auxUint;

		names.emplace_back(auxString);
		values.emplace_back(auxUint);
	}
}

bool check(const vector<uint>& values1, const vector<uint>& values2)
{
	if(values1.size() != values2.size()) throw logic_error("Sizes are different!");

	bool noProblem = true;

	for(uint i = 0; i < values1.size(); ++i)
	{
		if(values1[i] < values2[i])
		{
			noProblem = false;

			cout << "Case " << i << ":" << endl;
			cout << "	- Value 1: " << values1[i] << endl;
			cout << "	- Value 2: " << values2[i] << endl;
			cout << endl;
		}
	}

	return noProblem;
}

int main()
{
	vector<string> names1;
	vector<uint> values1;
	vector<string> names2;
	vector<uint> values2;

	read("../../results/simulations/Resultado1.txt", names1, values1);
	read("../../results/generated/simulations/Resultado1.txt", names2, values2);

	if(check(values1, values2))
	{
		cout << "All done, no problem! :)" << endl;
	}
	else
	{
		cout << "Oops! Seems like something went wrong :(" << endl;
	}
}