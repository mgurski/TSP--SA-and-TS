#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Timer.h"

using namespace std;

class TabuSearch {
private:
	vector<vector<int>> matrix;
	int instance_size;
	int** tabu_list;

	int max_iteration = 1000;
	Timer time_measuring;
	double stop_time = 300;
	int tenure = 10;
public:
	void read(string);
	int distance(vector<int>, int);

	int get_max_iteration() { return max_iteration; };
	int get_time() { return stop_time; };
	void set_time(double time) { stop_time = time; };
	vector<int> random_route();
	vector<int> tabu_search();
};

#endif
