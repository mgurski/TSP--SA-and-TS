#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
#include <ctime>
#include <fstream>
#include "Timer.h"

using namespace std;

void tests_comparison() {
	SimulatedAnnealing etap2;
	TabuSearch etap2_2;
	string file_name = "data";

	SimulatedAnnealing* etap2_tests;
	TabuSearch* etap2_2_tests;

	ifstream file;

	Timer time;

	vector<int> best_route;

	vector<int> instance_size;
	vector<int> route_lengths;

	double route_sum=0;
	double avg_route;

	int start_temp = etap2.get_temp();
	double end_temp = etap2.get_end_temp();
	double alphas[] = { 0.99, 0.999, 0.9999, 0.99999, 0.999999};
	double czasy[] = { 100,10000, 100000, 300000 };
	ofstream file_zapis;
	ofstream file_zapis2;


	for (int i = 0; i < 4; i++) {

		file_zapis.open("sim_annealing_test"+to_string(i)+".txt");
		file_zapis << "temp poczatkowa : " << start_temp << endl;
		file_zapis << "temp koncowa : " << end_temp << endl;
		file_zapis << "sta³a : " << alphas[i] << endl;
		file_zapis.close();

	
		for (int j = 10; j < 450; j++) {
			
			file_name += to_string(j);

			file.open(file_name + ".txt");

			if (file) {
				file.close();
/*
				file_zapis.open("sim_annealing_test" + to_string(i) + ".txt", ios::app);
				
				for (int k = 0; k < 5; k++) {
					etap2_tests = new SimulatedAnnealing();

					etap2_tests->read(file_name);
					etap2_tests->set_alpha(alphas[i]);

					time.time_start();
					best_route = etap2_tests->sim_annealing();
					time.time_stop();


					route_sum += etap2_tests->distance(best_route, best_route.size());
					delete etap2_tests;
				}

				avg_route = route_sum / 5;

				file_zapis << "data" << j << "   " << avg_route << "  czas : " << time.get_time() << endl;

				avg_route = 0, route_sum = 0;

				file_zapis.close();
				*/
				file_zapis.open("tabu_search_test" + to_string(i) + ".txt", ios::app);

				for (int k = 0; k < 5; k++) {

					etap2_2_tests = new TabuSearch();

					etap2_2_tests->read(file_name);

					etap2_2_tests->set_time(czasy[i]);

					time.time_start();
					best_route = etap2_2_tests->tabu_search();
					time.time_stop();

					route_sum += etap2_2_tests->distance(best_route, best_route.size());
					delete etap2_2_tests;
				}

				avg_route = route_sum / 5;

				file_zapis << "data" << j << "   " << avg_route << "  czas : " << time.get_time() << endl;

				file_zapis.close();
				avg_route = 0, route_sum = 0;

			}

			file_name = "data";
		}
	}
}

void auto_tests_sa() {
	SimulatedAnnealing etap2;
	string file_name = "data";

	SimulatedAnnealing * etap2_tests;

	ifstream file;

	Timer time;

	vector<int> best_route;

	vector<int> instance_size;
	vector<int> route_lengths;

	int start_temp = etap2.get_temp();
	double end_temp = etap2.get_end_temp();
	double alpha = etap2.get_alpha();
	
	ofstream file_zapis;

	file_zapis.open("simulated_annealing.txt");
	file_zapis << "temp poczatkowa : " << start_temp << endl;
	file_zapis << "temp koncowa : " << end_temp << endl;
	file_zapis << "sta³a : " << alpha << endl;

	for (int i = 10; i < 450; i++) {
		file_name += to_string(i);

		file.open(file_name + ".txt");

		if (file) {
			file.close();

			etap2_tests = new SimulatedAnnealing();

			etap2_tests->read(file_name);
			time.time_start();
			best_route = etap2_tests->sim_annealing();
			time.time_stop();

			file_zapis << "data" << i << "   " << etap2_tests->distance(best_route, best_route.size()) << "  czas : " << time.get_time() << endl;

			delete etap2_tests;

		}

		file_name = "data";
	}

	file_zapis.close();
}

void auto_tests_ts() {
	
	TabuSearch etap2;
	string file_name = "data";

	TabuSearch* etap2_tests;

	ifstream file;

	vector<int> best_route;

	int time = etap2.get_time();

	ofstream file_zapis;

	file_zapis.open("tabu_search.txt");
	file_zapis << "czas: " << time << endl;

	for (int i = 10; i < 450; i++) {
		file_name += to_string(i);

		file.open(file_name + ".txt");

		if (file) {
			file.close();

			etap2_tests = new TabuSearch();

			etap2_tests->read(file_name);

			best_route = etap2_tests->tabu_search();

			file_zapis << "data" << i << "   " << etap2_tests->distance(best_route, best_route.size()) << endl;

			delete etap2_tests;

		}

		file_name = "data";
	}

	file_zapis.close();
	
}


int main() {

	srand(time(NULL));
	/*
	vector<int> best_route;
	string file_name;
	bool quit = false;
	char x,y;

	while (!quit) {

		cout << "1. SA" << endl;
		cout << "2. TS" << endl;
		cout << "q. quit" << endl;

		cin >> x;

		SimulatedAnnealing* etap2;
		TabuSearch* etap2_2;

		switch (x) {
		case '1':
			etap2 = new SimulatedAnnealing();
			cout << "Enter the file name: " << endl;
			cin >> file_name;
			etap2->read(file_name);

			best_route = etap2->sim_annealing();

			for (int i = 0; i < best_route.size(); i++) {
				cout << best_route[i] << " ";
			}

			cout << endl;

			cout << etap2->distance(best_route, best_route.size());

			cout << endl;

			delete etap2;
			break;
		case '2':
			etap2_2 = new TabuSearch();
			cout << "Enter the file name: " << endl;
			cin >> file_name;
			etap2_2->read(file_name);

			best_route = etap2_2->tabu_search();

			for (int i = 0; i < best_route.size(); i++) {
				cout << best_route[i] << " ";
			}

			cout << endl;

			cout << etap2_2->distance(best_route, best_route.size());

			cout << endl;

			delete etap2_2;
			break;
		case 'q':
			quit = true;
			break;
		default:
			break;
		}

		cout << "enter anything to continue" << endl;
		cin >> y;
	}
	*/

	tests_comparison();
	auto_tests_ts();
	auto_tests_sa();
}