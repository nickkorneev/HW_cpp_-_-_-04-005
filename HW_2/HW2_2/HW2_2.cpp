#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer() : m_begin(clock_t::now()), duration(0) {}
	~Timer() {
		this->pause();
		std::cout << duration << " milliseconds" << std::endl;
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


int main() {
	{
		std::vector <int> v;
		for (auto i = 1; i < 100000; ++i)
		{
			v.push_back(100000 - i);
		}
		Timer t;
		std::sort(v.begin(), v.end());
		t.pause();
	}
	{
		std::array <int, 100000> a;
		for (auto i = 1; i < 100000; ++i)
		{
			a[i] = 100000 - i;
		}
		Timer t;
		std::sort(a.begin(), a.end());
		t.pause();
	}
	{
		std::deque <int> d;
		for (auto i = 1; i < 100000; ++i)
		{
			d.push_back(100000 - i);
		}
		Timer t;
		std::sort(d.begin(), d.end());
		t.pause();
	}
	{
		std::list <int> l;
		for (auto i = 1; i < 100000; ++i)
		{
			l.push_back(100000 - i);
		}
		Timer t;
		l.sort();
		t.pause();
	}
	{
		std::forward_list <int> fl;
		for (auto i = 1; i < 100000; ++i)
		{
			fl.push_front(i);
		}
		Timer t;
		fl.sort();
		t.pause();
	}
	return 0;
}