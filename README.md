### Advent of Code 2022 - C++ Edition 
This repo contains a small framework for running individual days, all days, and single days within a benchmark system, flags are as follows:

- `--day=n`: Will specify the day
- `--runs=n`: Will specify a number of runs to get the average over `n` given runs
- `--all`: Will run all days, takes precident over the `days` and `runs` flags
- `.` or `-`: Will automatically pick the last coded day.
- `--test`: Will run the contents of the test.h file, holds highest precident just to test random stuff.


This project does depend on `boost@1.80` which is easily installable on macOS using `brew install boost`. The cmake file should pick up the install location easily enough and link it all as needed. 
It should be possible to build the code simply by itialising the build with `cmake .`, then `make` will compile and finally `./entry .` will run the latest day.


#### Rules of engagement 
Since I'm aiming for execution speed below are my 'house rules' for testing

1. **Timing starts after the file is loaded**: Because disk reads are boring.
2. **No pre-parsing of inputs**: I'll allow parsing out the new line chars though, since I just read the file into a vector line by line, and because new lines are boring.
3. **Solutions should be sufficiently general**: A solution should provide an answer for any typical AoC input for that day and should avoid optimising too much for a specific input. Similarly it should probably solve any example.
4. **No Concurrency/Parallelism**: Creates a consistent playing field across all days vs some days not being parallelised.