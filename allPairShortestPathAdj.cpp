#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <list>
#include<sys/time.h>
using namespace std;
 
// Recursive function to print path of given vertex `u` from source vertex `v`
long gettime(){
    struct timeval start;
    gettimeofday(&start,NULL);
    return start.tv_sec*1000000+start.tv_usec;
}
void printPath(vector<vector<int>> const &path, int v, int u)
{
    if (path[v][u] == v) {
        return;
    }
    printPath(path, v, path[v][u]);
    cout << path[v][u] << ", ";
}
bool isPresentNode(vector<vector<int>> const &path, int v, int u,int m){
     if (path[v][u] == v) {
        return false;
    }
    if (path[v][u] == m){
        return true;
    }
    
    return isPresentNode(path, v, path[v][u],m);
    
}
// Function to print the shortest cost with path information between
// all pairs of vertices
void printSolution(vector<vector<int>> const &cost, vector<vector<int>> const &path)
{
    int n = cost.size();
    for (int v = 0; v < n; v++)
    {
        for (int u = 0; u < n; u++)
        {
            if (u != v && path[v][u] != -1)
            {
                cout << "The shortest path from " << v << " to " << u << " is ["
                    << v << ", ";
                printPath(path, v, u);
                cout << u << "]" <<"="<<cost[v][u]<< endl;
            }
        }
    }
}


void recommendationSystem(vector<vector<int>> const &cost, vector<vector<int>> const &path,int dest1,int dest2, int dest3,int n){
    int foo[n];
    if(isPresentNode(path,dest1,dest2,dest3)){
        cout<<"Destination 2 is on the way to destination1"<<endl;
        cout<<"Destination 2 at the distance "<<cost[dest1][dest3]<<" units"<<endl;
        cout<<"Actual Total Distance from start node to last destination "<<cost[dest1][dest2]+cost[dest2][dest3]<<endl;
        cout << "The shortest preference path from " << dest1 << " to " <<dest3 << " is ["
                    << dest1 << ", ";
                printPath(path, dest1, dest2);
                cout<<dest2<<", ";
                printPath(path,dest2,dest3);
                cout << dest3 << "]" <<endl;
        cout<<"Recommended Total Distance from start node to last destination "<<cost[dest1][dest2]<<endl;
        cout << "The shortest recommended path when destination 2 is visited 1st than destination 1 from " << dest1 << " to " <<dest2 << " is ["
                    << dest1 << ", ";
                printPath(path, dest1, dest3);
                cout<<dest3<<", ";
                printPath(path,dest3,dest2);
                cout << dest2 << "]" <<endl;
        cout<<"If you visit the destination 2 is then you will not travel duplicate path "<<cost[dest2][dest3]<<endl;

    }else if(cost[dest1][dest2]+cost[dest2][dest3]>cost[dest1][dest3]+cost[dest3][dest2]){
        cout<<"Actual Preference Distance "<<cost[dest1][dest2]+cost[dest2][dest3]<<endl;
        cout<<"Recommendation Distance "<<cost[dest1][dest3]+cost[dest3][dest2]<<endl; 
        cout<<"Destination 2 can be visited first reduces the distance "<<cost[dest1][dest2]+cost[dest2][dest3]-cost[dest1][dest3]-cost[dest3][dest2]<<endl;
        cout << "The shortest preference path from " << dest1 << " to " <<dest3 << " is ["
                    << dest1 << ", ";
                printPath(path, dest1, dest2);
                cout<<dest2<<", ";
                printPath(path,dest2,dest3);
                cout << dest3 << "]" <<endl;
        cout << "The shortest recommended path when destination 2 is visited 1st than destination 1 from " << dest1 << " to " <<dest2 << " is ["
                    << dest1 << ", ";
                printPath(path, dest1, dest3);
                cout<<dest3<<", ";
                printPath(path,dest3,dest2);
                cout << dest2 << "]" <<endl;
        
    }else{
        cout<<"Best Total Distance from start node to last destination "<<cost[dest1][dest2]+cost[dest2][dest3]<<endl;
        cout << "The shortest preference path from " << dest1 << " to " <<dest3 << " is ["
                    << dest1 << ", ";
                printPath(path, dest1, dest2);
                cout<<dest2<<", ";
                printPath(path,dest2,dest3);
                cout << dest3 << "]" <<endl;
    }
        

  

}

 
// Function to run the Floyd–Warshall algorithm
void floydWarshall(vector<vector<int>> const &adjMatrix,int start_node,int dest1,int dest2)
{
    // total number of vertices in the `adjMatrix`
    int n = adjMatrix.size();
 
    // base case
    if (n == 0) {
        return;
    }
 
    // cost[] and path[] stores shortest path
    // (shortest cost/shortest route) information
    vector<vector<int>> cost(n, vector<int>(n));
    vector<vector<int>> path(n, vector<int>(n));
 
    // initialize cost[] and path[]
    for (int v = 0; v < n; v++)
    {
        for (int u = 0; u < n; u++)
        {
            // initially, cost would be the same as the weight of the edge
            cost[v][u] = adjMatrix[v][u];
 
            if (v == u) {
                path[v][u] = 0;
            }
            else if (cost[v][u] != INT_MAX) {
                path[v][u] = v;
            }
            else {
                path[v][u] = -1;
            }
        }
    }
 
    // run Floyd–Warshall
    for (int k = 0; k < n; k++)
    {
        for (int v = 0; v < n; v++)
        {
            for (int u = 0; u < n; u++)
            {
                // If vertex `k` is on the shortest path from `v` to `u`,
                // then update the value of cost[v][u] and path[v][u]
 
                if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
                    && cost[v][k] + cost[k][u] < cost[v][u])
                {
                    cost[v][u] = cost[v][k] + cost[k][u];
                    path[v][u] = path[k][u];
                }
            }
 
            // if diagonal elements become negative, the
            // graph contains a negative-weight cycle
            if (cost[v][v] < 0)
            {
                cout << "Negative-weight cycle found!!";
                return;
            }
        }
    }
    
     // Print the shortest path between all pairs of vertices
    printSolution(cost, path);
    // recommendationSystem(cost, path,0,1,2,n);
    // recommendationSystem(cost, path,1,3,0,n);
    // recommendationSystem(cost, path,3,6,0,n);
    //ppt
    // recommendationSystem(cost, path,0,6,2,n);
    // recommendationSystem(cost, path,0,6,5,n);
   //recommendationSystem(cost, path,0,6,3,n);
   //recommendationSystem(cost, path,0,6,1,n);

    recommendationSystem(cost, path,start_node,dest1,dest2,n);

}
 
int main()
{
    // define infinity
    int I = INT_MAX;
    
 
    // given adjacency representation of the matrix
    // vector<vector<int>> adjMatrix =
    // {
    //     { 0, I, -2, I },
    //     { 4, 0, 3, I },
    //     { I, I, 0, 2 },
    //     { I, -1, I, 0 }
    // };
 
    // // Run Floyd–Warshall algorithm
    // floydWarshall(adjMatrix);
    vector<vector<int>> adjMatrix =
    {
        {0, 6, I, 3, 2, I, I}, 
        {3, 0, 2, I, I, I, I}, 
        {I, 2, 0, I, I, I, 3}, 
        {3, I, I, 0, 4, I, I}, 
        {I, I, 1, I, 0, I, I}, 
        {I, I, I, I, 2, 0, 2}, 
        {I, I, I, I, I, 2, 0}
    };
    int start_node;
    int dest1_node;
    int dest2_node;
    cout<<"Enter the start node: "<<endl;
    cin>>start_node;
    cout<<"Enter the destination 1: "<<endl;
    cin>>dest1_node;
    cout<<"Enter the destination 2: "<<endl;
    cin>>dest2_node;
    long start = gettime();
     floydWarshall(adjMatrix,start_node,dest1_node,dest2_node);
     long end = gettime();
     cout << "\n";
     cout<< "Time for execution: " << end-start << " microsec";
 
    return 0;
}