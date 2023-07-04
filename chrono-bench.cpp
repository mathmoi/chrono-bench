#include <iostream>
#include <chrono>
#include <cstdint>

template<typename clock>
void TestClock()
{
    typedef std::chrono::duration<float> fsec;

    auto test_duration = std::chrono::seconds(3);

    auto start = clock::now();
    
    typename clock::time_point now;
    typename clock::time_point last;
    typename clock::duration actual_duration;
    std::uint64_t iterations = 0;
    std::uint64_t distinct_values = 0;
    do 
    {
        ++iterations;

        now = clock::now();
        actual_duration = now - start;

        if (last != now)
        {
            ++distinct_values;
            last = now;
        }
    } while (actual_duration < test_duration);

    auto actual_duration_seconds = std::chrono::duration_cast<fsec>(actual_duration);

    std::cout <<"Test target duration : " <<test_duration.count() <<"s\n"
              <<"Actual duration : " <<actual_duration.count() <<"ns\n"
              <<"Iterations : " <<iterations <<'\n'
              <<"Calls per second : " <<iterations / actual_duration_seconds.count() <<"s\n"
              <<"Distinct values : " <<distinct_values <<'\n'
              <<"Average time between calls : " <<(actual_duration / iterations).count() <<"ns\n"
              <<"Average time between distinct time_points : " <<(actual_duration / distinct_values).count() <<"ns\n"
              <<std::endl;
}

int main(int argc, char** argv)
{
    std::cout <<"Testing steady_clock" <<std::endl;
    TestClock<std::chrono::steady_clock>();

    std::cout <<"Testing system_clock" <<std::endl;
    TestClock<std::chrono::system_clock>();

    std::cout <<"Testing high_resolution_clock" <<std::endl;
    TestClock<std::chrono::high_resolution_clock>();
    

    return 0;
}