#ifndef MINIMAL_CONSOLE_OUTPUTTER
#define MINIMAL_CONSOLE_OUTPUTTER

#include "hayai_outputter.hpp"
#include "hayai_console.hpp"

namespace hayai
{
    // Modified from hayai::ConsoleOutputter to reduce the amount of clutter on the screen.

    class MinimalConsoleOutputter : public ConsoleOutputter {
    public:
        virtual void EndTest(const std::string& fixtureName,
                             const std::string& testName,
                             const TestParametersDescriptor& parameters,
                             const TestResult& result) {

            showTime(_stream << std::setw(31) << "Total: ", result.TimeTotal()) << '\n';
            _stream << "             Iterations:\n";

            showTime(_stream << std::setw(31) << "Average time: ", result.IterationTimeAverage()) << '\n';
            showTime(_stream << std::setw(31) << "Fastest time: ", result.IterationTimeMinimum()) << '\n';
            showTime(_stream << std::setw(31) << "Slowest time: ", result.IterationTimeMaximum()) << '\n';
        }

    private:
        std::ostream& showTime(std::ostream& stream, const double ns) {
            _stream << std::setprecision(2);

            if (ns >= 1.e9) {
                return _stream << ns / 1.e9 << " s";
            } else if (ns >= 1.e6) {
                return _stream << ns / 1.e6 << " ms";
            } else if (ns >= 1.e3) {
                return _stream << ns / 1.e3 << " us";
            } else {
                return _stream << ns / 1.e0 << " ns";
            }
        }
    };
}

#endif // MINIMAL_CONSOLE_OUTPUTTER
