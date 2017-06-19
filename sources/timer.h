#include <iostream>
#include <chrono>

template <typename TimeT = std::chrono::nanoseconds, typename ClockT = std::chrono::high_resolution_clock>
class TimeTimer
{
  public:
	TimeTimer(int executionTimes)
		: m_executionTimes(executionTimes)
	{
	}

	virtual ~TimeTimer() = default;

	template <typename F, typename... Args>
	void measure(F func, Args &&... args)
	{
		std::cout << "run " << func << " for " << m_executionTimes << " times..." << std::endl;

		auto start = ClockT::now();

		for (auto i = 0; i < m_executionTimes; ++i)
		{
			func(std::forward<Args>(args)...);
		}

		auto duration = std::chrono::duration_cast<TimeT>(ClockT::now() - start).count();

		auto avgTimePerCall = duration / m_executionTimes;

		std::cout << std::endl << duration << " ns average time per call" << std::endl;
	}

  private:
	int m_executionTimes;
};
