Course Allocation System
This is a C++ application that solves a course-to-professor assignment problem using the Ford-Fulkerson algorithm to find the maximum flow in a specially constructed graph. The system reads course and professor data from text files and outputs the optimal assignments to a new file.

How it Works
The core of this project is a maximum flow algorithm applied to a bipartite graph. The graph is constructed as follows:

A source node (S) is connected to all professor nodes.

A sink node (T) is connected to all course nodes.

Professor nodes are connected to the course nodes they are qualified to teach.

The capacities of the edges define the constraints:

The capacity from the source node to each professor node is based on the professor's type, representing the number of courses they can teach.

The capacity from each professor node to a course node is 2, allowing a course to be "half-taught" by two professors if necessary.

The capacity from each course node to the sink node is 2, ensuring that a course is taught by a maximum of two professors.

The fordFulkerson function calculates the maximum flow from the source to the sink. The flow on each edge between a professor and a course represents the assignment.

Priority-based BFS
A key feature of this implementation is the modification of the Breadth-First Search (BFS) to prioritize certain assignments. When searching for an augmenting path, the bfs function gives higher priority to courses that have already been partially assigned (flowPassed[v][MAX-1] == 1). This is intended to encourage the completion of partial assignments before starting new ones.

Getting Started
Prerequisites
A C++ compiler (like g++).

Input files named professors.txt and courses.txt in the same directory. You can also use the professors_big.txt and courses_big.txt provided in the code.

Input File Format
courses.txt
This file should contain a list of all available course names, with each name on a new line.

CourseA
CourseB
CourseC
professors.txt
The first line of this file should contain three integers: x1, x2, and x3, representing the number of professors of each type. Following this, each professor's entry consists of two lines:

The professor's name and the number of courses they are qualified to teach.

A space-separated list of the course names they can teach.

1 1 1
Professor1 2
CourseA CourseB
Professor2 1
CourseB
Professor3 1
CourseA
Compiling and Running
Compile the code:

Bash

g++ -std=c++11 -o course_allocator main.cpp
Run the executable:

Bash

./course_allocator
Output
The program will generate a file named output.txt containing the course assignments. Each line in the output file will specify which professor is teaching which course.

Professor1 teaches CourseA
Professor2 teaches CourseB
Professor3 teaches CourseC
Potential Improvements
Command-line Arguments: Modify the code to accept input and output file names as command-line arguments instead of hardcoding them.

Error Handling: Add more robust error handling for file I/O, especially if the input files are not found or are improperly formatted.

Dynamic Sizing: Replace the hardcoded MAX value with a dynamic data structure (like std::vector) to handle a variable number of professors and courses.

Alternative Algorithms: Explore other maximum flow algorithms like Edmonds-Karp or Dinic's algorithm, which might offer better performance on certain graph structures.
