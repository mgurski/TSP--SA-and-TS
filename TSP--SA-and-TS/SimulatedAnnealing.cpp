#include "SimulatedAnnealing.h"

void SimulatedAnnealing::read(string name)
{
	int distance_reader;
	string instance_name;
	vector<int> tmp;

	ifstream file;

	file.open(name + ".txt");

	if (!file) {
		cout << "Unable to open file" << endl;
	}
	else {

		file >> instance_name;
		file >> instance_size;

		for (int i = 0; i < instance_size; i++) {
			for (int j = 0; j < instance_size; j++) {

				file >> distance_reader;
				tmp.push_back(distance_reader);
			}

			matrix.push_back(tmp);
			tmp.clear();
		}

	}

	file.close();
}

int SimulatedAnnealing::distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size - 1; i++) {
		sum += matrix[salesmans_route[i]][salesmans_route[i + 1]];
	}
	sum += matrix[salesmans_route[route_size - 1]][salesmans_route[0]];

	return sum;
}

double SimulatedAnnealing::probability(vector<int> old_route, vector<int> new_route)
{		
	int difference = distance(new_route, new_route.size()) - distance(old_route, old_route.size());

	return exp(-(difference / current_temp));
}

void SimulatedAnnealing::lower_the_temperature()
{
	current_temp = alpha * current_temp;
}

vector<int> SimulatedAnnealing::swap(vector<int> old_route)
{
	vector<int> new_route = old_route;

	int a = rand() % (instance_size-1) + 1;
	int b = rand() % (instance_size-1) + 1;
	while (a == b) b = rand() % (instance_size-1) + 1;

	int temp = old_route[a];
	new_route[a] = old_route[b];
	new_route[b] = temp;

	return new_route;
}

vector<int> SimulatedAnnealing::sim_annealing()
{

	vector<int> current_route;
	vector<int> new_route;
	vector<int> best_route;
	//starting from natural permutation
	for (int i = 0; i < instance_size; i++) {
		current_route.push_back(i);
	}

	best_route = current_route;
	
	while (current_temp > end_temp) {

	//creating a new route by swaping two random vertices
		new_route = swap(current_route);

	//checking if the new route is better than the current route
		if (distance(new_route, new_route.size()) < distance(current_route, current_route.size())) {
			current_route = new_route;
		}
	//even if not, we have a chance to accept it. The higher the temperature the higher the chance
		else if (((double)rand() / (double)RAND_MAX) < probability(current_route, new_route)) {
			current_route = new_route;
		}
		if (distance(current_route, current_route.size()) < distance(best_route, best_route.size())) {
			best_route = current_route;
		}
	//lowering the temp
		lower_the_temperature();

	}

	return best_route;
}
