#include<iostream>
#include<vector>
#include<set>
#include<array>
#include<chrono>
#include<algorithm>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now()), duration(0) {}
	~Timer() {
		this->pause();
		std::cout << duration << " duration(in milliseconds)" << std::endl;
	}
	void pause() {
		auto end = clock_t::now();
		duration += std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin).count();
	}
	void goon() {
		m_begin = clock_t::now();
	}
private:
	time_point_t m_begin;
	int duration;
};

int main()
{
	srand(0);
	std::array <int, 100000> x;
	for (int i = 0; i < x.size(); ++i)
		x[i] = rand();
	std::cout << "n=" << x.size() << std::endl;
	std::sort(x.begin(), x.end());
	{
		std::set <int> s;
		Timer t;
		for (int i = 0; i < x.size(); ++i)
			s.insert(x[i]);
		t.pause();
		std::cout << "set duration = ";
	}
	{
		std::vector <int> v;
		Timer t;
		for (int i = 0; i < x.size(); ++i)
			v.push_back(x[i]);
		std::sort(v.begin(), v.end());
		t.pause();
		std::cout << "vector duration = ";
	}
	return 0;
}