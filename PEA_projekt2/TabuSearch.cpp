#include "TabuSearch.h"

void TabuSearch::read(string name)
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

	this->tabu_list= new int* [instance_size];
	for (int i = 0; i < instance_size; i++)
		this->tabu_list[i] = new int[instance_size];

}

int TabuSearch::distance(vector<int> salesmans_route, int route_size)
{
	int sum = 0;

	for (int i = 0; i < route_size - 1; i++) {
		sum += matrix[salesmans_route[i]][salesmans_route[i + 1]];
	}
	sum += matrix[salesmans_route[route_size - 1]][salesmans_route[0]];

	return sum;
}

vector<int> TabuSearch::random_route()
{
	vector<int> tmp;
	vector<int> random_route;
	int random_number;

	random_route.push_back(0);

	for (int i = 1; i < instance_size; i++) {
		tmp.push_back(i);
	}

	for (int j = 1; j < instance_size; j++) {
		random_number = rand() % (instance_size-j);
		random_route.push_back(tmp[random_number]);
		tmp.erase(tmp.begin() + random_number);
	}

	return random_route;
}

vector<int> TabuSearch::tabu_search()
{

	//init tabu list
	for (int i = 0; i < instance_size; i++) {
		for (int j = 0; j < instance_size; j++) {
			this->tabu_list[i][j] = 0;
		}
	}

	vector<int> current_route;
	vector<int> best_route;
	vector<int> neighbour_route;
	vector<int> next_route;

	int tabu_i = 0, tabu_j = 0;
	int counter = 0;
	int tenure = instance_size;


	//starting route will be a natural permutation
	for (int i = 0; i < instance_size; i++) {
		current_route.push_back(i);
	}

	best_route = current_route;

	time_measuring.time_start();

	while (time_measuring.get_time() < stop_time) {

		int mval = -1;

		//swaping
		for (int i = 1; i < instance_size; i++) {
			for (int j = i + 1; j < instance_size; j++) {

				neighbour_route = current_route;

				int tmp = neighbour_route[j];
				neighbour_route[j] = neighbour_route[i];
				neighbour_route[i] = tmp;


				int length_difference = distance(current_route, current_route.size()) - distance(neighbour_route, neighbour_route.size());

				if (mval == -1) {
					if (tabu_list[current_route[i]][current_route[j]] == 0 || (distance(neighbour_route, neighbour_route.size()) < distance(best_route, best_route.size()))) {
						mval = length_difference;
						next_route = neighbour_route;
						tabu_i = current_route[i];
						tabu_j = current_route[j];
					}
				}
				else if (length_difference > mval) {
					if (tabu_list[current_route[i]][current_route[j]] == 0 || (distance(neighbour_route, neighbour_route.size()) < distance(best_route, best_route.size()))) {
						mval = length_difference;
						next_route = neighbour_route;
						tabu_i = current_route[i];
						tabu_j = current_route[j];
					}
				}
		
			}
		}

				current_route = next_route;
			
				if (distance(best_route, best_route.size()) > distance(current_route, current_route.size())) {
					best_route = current_route;
					counter = 0;
				}
				else {
					counter++;
				}

				//tabu list verification

				for (int k = 0; k < instance_size; k++) {
					for (int l = 0; l < instance_size; l++) {
						if (this->tabu_list[k][l] > 0) {
							this->tabu_list[k][l] -= 1;
						}
					}
				}

				this->tabu_list[tabu_i][tabu_j] = tenure;
				this->tabu_list[tabu_j][tabu_i] = tenure;

				//critical event

				if (counter > max_iteration) {
					current_route = random_route();

					if (distance(current_route, current_route.size()) < distance(best_route, best_route.size())) {
						best_route = current_route;
					}
					counter = 0;
				}

				time_measuring.time_stop();
			}

			return best_route;
		}
