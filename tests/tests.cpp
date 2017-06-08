#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>

#include "../sources/table.h"


int main(int argc, char const * argv[])
{

    auto tree_buf = tree_streambuf();

	// set treebuf as rdbuf for cout
	std::streambuf* defaultCout = std::cout.rdbuf();
	std::cout.rdbuf(&tree_buf);

    // add cout to tree_buf sinks
    tree_buf.add_sink(defaultCout);

    std::ofstream logstream("cout.log");

    // add logfile cout.log to sinks
    tree_buf.add_sink(logstream.rdbuf());


    // cout will print on console and file...

	std::cout << "================================================" << std::endl;


    // try to read from buffer fails
    //std::clog << "tree_buf: " << tree_buf.sgetc();

	std::cout << "command line: ";
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;

	std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
	std::cout << "current time: " << std::put_time(&tm, "%F %T UTC%z") << std::endl;

	std::cout << "------------------------------------------------" << std::endl;

	const auto r = std::random_device{}();
	std::cout << "some random number: " << r << std::endl;

	const auto s1 = std::string{
R"(464ZWaijyOIkiyb8u586
79xm7Qoa6uWWy87933oD
UKcK0tTuoj5kspAo4vEp
sOOk718PYsKbg1LEHUSQ
Sg8rspmQk4AsoBbqTrIw
3yeohMXiyILtQ5vFzcDc
StBq4KXLh0Hn9ZgItczf
KfJdldwqqH2n7uu4LMAv
pts7Tngr7wJIeEB5SRPs
fc1JIebAcVOHVN0X4KSp)"
};
	std::copy(s1.begin(), s1.end(), std::ostream_iterator<char>(std::cout));
	std::cout << std::endl;

	const auto s2 = std::string{
R"(Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.   

Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat.   

Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.)"
	};
	std::cout.write(s2.data(), s2.size());
	std::cout.put('\n');

	// restore cout to default buffer
	std::cout.rdbuf(defaultCout);

	std::cout << "Default output on cout only...";
}
