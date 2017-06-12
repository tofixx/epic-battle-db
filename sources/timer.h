#include <iostream>

template<typename TimeT = std::chrono::nanoseconds, typename ClockT = std::chrono::high_resolution_clock>
class TimeTimer
{
public:
	TimeTimer(int executionTimes)
	: m_executionTimes(executionTimes)
	{

	}

 template<typename F, typename ...Args>
    typename TimeT::rep measure(F func, Args&&... args)
    {
		std::cout << "run " << func << " for " << m_executionTimes << " times..." << std::endl;
        
		auto start = ClockT::now();
		
		for(auto i = 0; i < m_executionTimes; ++i)
		{
        	func(std::forward<Args>(args)...);
		}

        auto duration = std::chrono::duration_cast<TimeT>(ClockT::now() - start).count();

        return duration / m_executionTimes;
    }

private:
	int m_executionTimes;
   
};
