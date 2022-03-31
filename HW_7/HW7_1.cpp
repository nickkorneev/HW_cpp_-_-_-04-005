#include <iostream>
#include <vector>
#include <random>
#include <future>

using namespace std;

long random_circle_sampling(long points_number){
    std::random_device ran;
    std::mt19937 gen(ran());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    long N1 = 0;
    for(long i = 0; i < points_number; i++){
        double x = dist(gen);
        double y = dist(gen);
        if(x*x + y*y <= 1.0){
            N1++;
        }
    }
    return N1;
}

double counted_pi(long points, int N){
    long points_N = points / N;

    vector<future<long>> fu;
    for(int t = 0; t < N; t++){
        fu.emplace_back(async(launch::async, random_circle_sampling, points_N));
    }

    long tot_N1 = 0;
    for(future<long>& f : fu){
        tot_N1 += f.get();
    }

    double pi = 4.0 * (double) tot_N1 / (double) points;
    return pi;

}


int main() {
    cout.precision(32);

    long points = 100000;
    int N = 8;
    double pi = 3.14159265358979323846;
    double our_pi = counted_pi(points, N);
    cout << "pi: " <<pi << endl;
    cout << "counted_pi:  " <<our_pi << endl;

    return 0;
}