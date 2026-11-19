#include "cucumber/gherkin/AstBuilder.hpp"
#include "cucumber/gherkin/Parser.hpp"
#include <charconv>
#include <chrono>
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

int main(int argc, char** argv)
{
    try
    {
        constexpr std::size_t defaultIterations = 100;
        std::size_t iterations = defaultIterations;

        if (argc > 1)
        {
            const std::string argument(argv[1]);                 // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            const auto* end = argument.data() + argument.size(); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            const auto result = std::from_chars(argument.data(), end, iterations);

            if (result.ec != std::errc{} || result.ptr != end || iterations == 0)
            {
                throw std::invalid_argument("Usage: cucumber_gherkin_benchmark [positive iterations] [feature files...]");
            }
        }

        std::vector<std::pair<std::string, std::string>> sources;
        const auto load = [&sources](const std::string& path)
        {
            std::ifstream input(path, std::ios::binary);

            if (!input.is_open())
            {
                throw std::runtime_error("Unable to open benchmark input: " + path);
            }

            std::string source{ std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>() };

            if (input.bad())
            {
                throw std::runtime_error("Unable to read benchmark input: " + path);
            }

            sources.emplace_back(path, std::move(source));
        };

        for (int i = 2; i < argc; ++i)
        {
            load(argv[i]); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }

        if (sources.empty())
        {
            load(GHERKIN_BENCHMARK_FEATURE);
        }

        cucumber::gherkin::Parser<cucumber::gherkin::AstBuilder> parser;
        const auto parse = [&parser](const auto& source)
        {
            const auto document = parser.Parse(source.first, source.second);

            if (!document.feature)
            {
                throw std::invalid_argument("Benchmark input has no Feature: " + source.first);
            }

            return document.feature->children.size();
        };

        std::size_t bytes = 0;

        for (const auto& source : sources)
        {
            (void)parse(source);
            bytes += source.second.size();
        }

        std::size_t checksum = 0;
        const auto start = std::chrono::steady_clock::now();

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            for (const auto& source : sources)
            {
                checksum += parse(source);
            }
        }

        const auto seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        const double documents = static_cast<double>(iterations) * static_cast<double>(sources.size());
        const double mib = static_cast<double>(iterations) * static_cast<double>(bytes) / (1024.0 * 1024.0);

        std::cout << "backend,iterations,files,bytes_per_iteration,seconds,documents_per_second,MiB_per_second,checksum\n"
                  << GHERKIN_REGEX_BACKEND << ',' << iterations << ',' << sources.size() << ',' << bytes << ',' << seconds << ','
                  << documents / seconds << ',' << mib / seconds << ',' << checksum << '\n';
    }
    catch (const std::exception& error)
    {
        std::cerr << "Benchmark failed: " << error.what() << '\n';

        return 1;
    }
}
