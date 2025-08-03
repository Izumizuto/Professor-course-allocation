#include<bits/stdc++.h>

using namespace std;

const int MAX = 500; 
int capacities[MAX][MAX] = {0};
int flowPassed[MAX][MAX] = {0};
vector<int> course_prof_graph[MAX];

bool bfs(int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[MAX];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Declare the priority order, if a course has already been picked by one professor to be taught half
        // give that course higher priority than a course that has not been picked before.

        vector<int> courses_used_half;
        if ((find(course_prof_graph[u].begin(),course_prof_graph[u].end(), MAX-1) == course_prof_graph[u].end()) && u != 0){
            vector<int> courses_used_not;
            for(int v:course_prof_graph[u]){
                if(flowPassed[v][MAX-1] == 1){
                    courses_used_half.push_back(v);
                } else if (flowPassed[v][MAX-1] == 2){
                    courses_used_not.push_back(v);
                }
            }
            courses_used_half.insert(courses_used_half.end(), courses_used_not.begin(), courses_used_not.end());
        } else{
            courses_used_half = course_prof_graph[u];
        }

        // cout<<u<<" ";
        // for(auto i: courses_used_half){
        //     cout<<i<<" ";
        // }
        // cout<<endl;
        for (auto v: courses_used_half) { // This makes sure that the course with higher priority is picked first
            if (visited[v] == false && flowPassed[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}
 
// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    
    for (u = 0; u < MAX; u++)
        for (v = 0; v < MAX; v++)
            flowPassed[u][v] = capacities[u][v];
 
    int parent[MAX]; // This array is filled by BFS and to
                   // store path
 
    int max_flow = 0; // There is no flow initially
 
    // Augment the flow while there is path from source to
    // sink
    while (bfs(s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, flowPassed[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            flowPassed[u][v] -= path_flow;
            flowPassed[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}

string findKeyByValue(const unordered_map<string, int>& map, int value) {
    for (const auto& pair : map) {
        if (pair.second == value) {
            return pair.first;
        }
    }
}

int main() {
    // ifstream profFile("professors.txt");
    // ifstream courseFile("courses.txt");
    // ofstream outputFile("output.txt");

    ifstream profFile("professors_big.txt");
    ifstream courseFile("courses_big.txt");
    ofstream outputFile("output_big.txt");

    if (!profFile.is_open() || !courseFile.is_open()) {
        cerr << "Could not open the given input files" << endl;
        return 1;
    }

    string line;
    unordered_map<string, int> courseToNode;
    unordered_map<string, int> professorToNode;
    int professorNode = 1; // Start from 1, 0 will be source

    // Read all the courses and assign them numerical values
    int courseNode = MAX/2;
    while(getline(courseFile, line)){
        istringstream iss(line);
        string courseName;
        iss >> courseName;
        courseToNode[courseName] = courseNode++;
    }

    for(auto & coursePair: courseToNode){
        cout<<coursePair.first<<" "<<coursePair.second<<endl;
    }
    getline(profFile, line);
    istringstream iss(line);
    int x1, x2, x3 = 0; // Number of professors of each type
    iss >> x1 >> x2 >> x3;
    cout<<"Profs of each type "<<x1<<" "<<x2<<" "<<x3<<" "<<endl;
    int courseWeight = 1; // Can be 1, 2, 3 depending upon proftype.

    // Create the adjacency graph between professor and course
    while (getline(profFile, line)) {
        istringstream iss(line);
        string profName;
        int numCourses;
        iss >> profName >> numCourses;
        professorToNode[profName] = professorNode;

        // Add edges from professor to courses
        getline(profFile, line);
        istringstream lss(line);
        for (int i = 0; i < numCourses; ++i) {
            string course;
            lss >> course;
            int courseId = courseToNode[course];
            // cout<<"Prof "<<profName<<" wants to take "<<course<<endl;
            course_prof_graph[professorNode].push_back(courseId); // Create adjacency matrix
            // course_prof_graph[courseId].push_back(professorNode);
            capacities[professorNode][courseId] = 2; // Give each edge weight (can be taken by atmost 2 profs)
            // capacities[courseId][professorNode] = 1;
        }
        
        course_prof_graph[0].push_back(professorNode);
        // course_prof_graph[professorNode].push_back(0);
        capacities[0][professorNode] = courseWeight; // Give each edge from source to professor weight equal to number of courses they can take
        // capacities[professorNode][0] = courseWeight;
        cout<<"Professor "<<professorNode<<" assigned capacity "<<courseWeight<<endl;
        professorNode++;
        if(professorNode <= x1){
            courseWeight = 1;
        } else if(professorNode > x1 && professorNode <= x1 + x2){
            courseWeight = 2;
        } else{
            courseWeight = 3;
        }
    }

    for(auto coursePair: courseToNode){
        capacities[coursePair.second][MAX-1] = 2; // Give weight of each edge from course to sink as 2 (since each course can be taught atmost by 2 profs).
        // course_prof_graph[MAX-1].push_back(coursePair.second);
        course_prof_graph[coursePair.second].push_back(MAX-1);
    }

    int maxFlow = fordFulkerson(0, MAX - 1);
    cout<<"Max flow is "<<maxFlow<<endl;

    // Output the assignments
    for (int i = 1; i < professorNode; ++i) {
        for (int courseNode : course_prof_graph[i]) {
            if (flowPassed[i][courseNode]!=capacities[i][courseNode]) {
                outputFile << findKeyByValue(professorToNode, i) << " teaches " << findKeyByValue(courseToNode, courseNode)<< endl;
            }
        }
    }


    // for(int i=0;i<MAX;i++){
    //     for(int j=0; j<MAX; j++){
    //         cout<<flowPassed[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    profFile.close();
    courseFile.close();
    outputFile.close();

    return 0;
}