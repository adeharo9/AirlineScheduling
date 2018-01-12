# AirlineSheduling
Program for solving the airline scheduling problem, selecting the minimum number of pilots that can perform a given set of routes between cities given some constraints on their workflow.

## How to compile?
From the base directory of the project, simply execute, from command line, the following command:

$ `make`

## How to execute?
Once compiled, from the base directory of the project simply execute, from command line, the following command:

$ `./AirlineScheduling`

The instructions on how to properly set an execution session of the program will appear on screen.

$ `./AirlineScheduling [-12hL] [-a algorithm] [-AM]`

**Options**
- `-1`: Executes the selected algorithms with version 1 of the problem.
- `-2`: Executes the selected algorithms with version 2 of the problem.
- `-h`, `--help`: Shows the help message.
- `-L`, `--ALL`: Executes the selected algorithms with all versions of the problem.
------
- `-a`, `--algorithm` `ALG`: Executes the program with the algorithm identified by its descriptor `ALG`. Available descriptors are:
    - `DI`: Dinic's blocking flow algorithm."
    - `EK`: Edmonds-Karp algorithm.
    - `FF`: Ford-Fulkerson method with DFS.
    - `ALL`: Executes all previously named algorithms secuentially.
------
- `-A`, `--auto`: Executes automatic data input.
- `-M`, `--manual`: Executes manual data input.
