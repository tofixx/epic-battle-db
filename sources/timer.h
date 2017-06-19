#include <iostream>
#include <chrono>

template <typename TimeNs = std::chrono::nanoseconds, typename TimeMs = std::chrono::milliseconds, typename TimeS = std::chrono::seconds,typename ClockT = std::chrono::high_resolution_clock>
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
		std::cout << "\x1B[33mrun " << typeid(func).name() << " for " << m_executionTimes << " times...\x1B[0m\n" << std::endl;

		auto start = ClockT::now();

		for (auto i = 0; i < m_executionTimes; ++i)
		{
			func(std::forward<Args>(args)...);
		}

		auto durationS = std::chrono::duration_cast<TimeS>(ClockT::now() - start).count();
		auto durationMs = std::chrono::duration_cast<TimeMs>(ClockT::now() - start).count();
		auto durationNs = std::chrono::duration_cast<TimeNs>(ClockT::now() - start).count();

		auto avgTimePerCall = durationNs / m_executionTimes;

		std::cout << std::endl << "\x1B[32m";

		if (durationS != 0) {
			durationMs -= durationS * 1000;
			durationNs -= durationS * 1e+9;
			std::cout << durationS << "s ";
		}

		if (durationMs != 0) {
			durationNs -= durationMs * 1e+6;
			std::cout << durationMs << "ms ";
		}

		std::cout << durationNs << "ns total duration; " << avgTimePerCall << "ns average time per call\x1B[0m\n" << std::endl;
	}

  private:
	int m_executionTimes;
};
