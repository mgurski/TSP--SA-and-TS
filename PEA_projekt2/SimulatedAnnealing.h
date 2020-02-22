#ifndef SIMMULATEDANNEALING_H
#define SIMMULATEDANNEALING_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

class SimulatedAnnealing {
private:
	vector<vector<int>> matrix;
	int instance_size;

	double current_temp = 100;
	double end_temp = 0.001;
	double alpha = 0.999999;

public:
	void read(string);
	int distance(vector<int>, int);

	double probability(vector<int>, vector<int>);
	void lower_the_temperature();

	vector<int> swap(vector<int>);
	vector<int> sim_annealing();

	double get_temp() { return current_temp; };
	double get_end_temp() { return end_temp; };
	double get_alpha() { return alpha; };
	void set_alpha(double a) { alpha = a; };
};

#endif
