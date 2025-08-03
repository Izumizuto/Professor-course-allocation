📚 Course Allocation Using Max Flow (Ford–Fulkerson)
This project assigns courses to professors using the Ford–Fulkerson algorithm for maximum flow in a bipartite graph. It ensures that:

Professors are assigned courses based on their teaching capacity.

Courses can be taught by a maximum of two professors.

Priority is given to partially filled courses before assigning new ones.

🚀 Features
Uses Ford–Fulkerson max flow to optimally assign courses.

Supports different professor types (1-course, 2-course, or 3-course load).

Reads input from files (professors_big.txt, courses_big.txt).

Outputs allocation results to output_big.txt.

Respects constraints: each course can have at most two professors.

📂 Input File Format
1️⃣ courses_big.txt
Each line contains a course name.

nginx
Copy
Edit
CSE101
CSE102
MTH101
PHY101
2️⃣ professors_big.txt
First line: Three integers → number of professors with load 1, load 2, load 3.

Following lines:

Professor name and number of preferred courses.

Next line contains the list of course codes they are willing to teach.

Example:

Copy
Edit
2 2 1
ProfA 2
CSE101 MTH101
ProfB 3
CSE101 CSE102 PHY101
ProfC 1
PHY101
ProfD 2
MTH101 CSE102
ProfE 1
CSE102
⚙️ How It Works
Graph Representation

Source node (0) connects to professors (capacities = course load).

Professors connect to preferred courses (capacity = 2).

Courses connect to sink node (MAX-1) (capacity = 2).

Priority Allocation

Courses already partially assigned are prioritized for the next professor.

Ford–Fulkerson Execution

BFS finds augmenting paths.

Residual capacities are updated.

Maximum flow determines optimal assignment.

Output

Writes assigned professor–course pairs to output_big.txt.

▶️ How to Run
Compile & Run
bash
Copy
Edit
g++ -std=c++17 -O2 main.cpp -o allocation
./allocation
Expected Output
Console shows max flow and debug info.

output_big.txt contains assignments:

python-repl
Copy
Edit
ProfA teaches CSE101
ProfB teaches CSE102
ProfC teaches PHY101
...
📊 Example Flow
With the example inputs:

Max Flow: 5 (total assigned courses).

Assignments:

nginx
Copy
Edit
ProfA teaches CSE101
ProfB teaches CSE102
ProfC teaches PHY101
ProfD teaches MTH101
ProfE teaches CSE102
📝 Notes
Adjust MAX constant if number of nodes > 500.

Make sure professors_big.txt and courses_big.txt are in the same folder as the executable.

For smaller datasets, replace file names inside main() with professors.txt and courses.txt.

📌 Files in Repo
bash
Copy
Edit
├── main.cpp                # Core allocation logic
├── professors_big.txt      # Professor preferences
├── courses_big.txt         # List of courses
├── output_big.txt          # Generated assignments
└── README.md               # Documentation
Do you want me to also include a diagram of the flow network (Source → Professors → Courses → Sink) in the README so it’s more visual for GitHub? It could make it stand out a lot more.









Ask ChatGPT
