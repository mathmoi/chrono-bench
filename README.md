# chrono-bench

A simple benchmark for the std::chrono clocks implementations. 

I wanted to convince myself that the differents implementations of std::chrono were
both fast and accurate. A fast implementation will returns a result really quick. An 
accurate implementation will return differents results for really close and subsequent 
calls.

## A note on accuracy

A typical implementation of a std::chrone clock returns a time_point specified in 
nanoseconds. However there is no garuanty that the clock is that accurate, in fact it's
probably not the case. The fact is that two successive calls to the clock might read the
same value from the underlying clock resulting in the same time_point returned each time.
The real accuracy of the clock is the frequency at which the returned value changes.
This is the "Average time between distinct time_points" that this benchmark outputs.