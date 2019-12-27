#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <math.h>
#define START 1 // Starting vertex
#define END 6   // Ending vertex
#define P 1     // Permanent
#define T 0     // Temporary
#define INFINITY 9999
ifstream in("dijk_in.txt");
ofstream out("Dij_Out.txt");
struct node
{
    double label; // label of the vertex
    int status;   // status of the vertex P or T
    int pred;     // Predecessor of the vertex
} vertex[50];     // vertex array with three attributes
double a[50][50]; // Weight matrix for the edges
int n;            // number of vertices
int e;            // number of edges
main()
{
    int i, j, u, v;
    int path[50];
    double d;
    double dijkstra(int s, int t);
    void short_path(int v);
    clrscr();
    in >> n >> e;
    out << "The number of vertices: " << n << endl;
    out << "The number of edges: " << e << endl;
    for (u = 0; u <= n; u++)
        for (v = 0; v <= n; v++)
            a[u][v] = INFINITY;
    do
    {
        in >> u >> v >> d;
        a[u][v] = d;
    } while (!in.eof());
    in.close();
    out << "\nThe Adjacency matrix(Weight matrix):" << endl;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            out << a[i][j] << " ";
        out << endl;
    }
    if (dijkstra(START, END))
    {
        out << "\nThe shortest distance from " << START << " to " << END << " :
                                                                            "<<dijkstra(START,END)<<endl;
            out
            << "\nThe shortest path : ";
        short_path(END);
    }
    else
        out << "There is no path:"
            << "\n";
    cin.get();
    return 0;
}
double dijkstra(int s, int t)
{
    int i, j, k;
    double min;
    for (j = 1; j <= n; j++)
    {
        vertex[j].label = INFINITY;
        vertex[j].status = T;
    }
    vertex[s].label = 0;
    vertex[s].status = P;
    vertex[s].pred = 0;
    k = s;
    do
    {
        for (j = 1; j <= n; j++)
        {
            if ((vertex[j].status == T) && (a[k][j] != INFINITY))
            {
                if (vertex[j].label > vertex[k].label + a[k][j])
                {
                    vertex[j].label = vertex[k].label + a[k][j];
                    vertex[j].pred = k;
                }
            }
        }
        k = 0;
        min = INFINITY;
        for (i = 1; i <= n; i++)
        {
            if ((vertex[i].status == T) && (vertex[i].label < min))
            {
                min = vertex[i].label;
                k = i;
            }
        }
        vertex[k].status = P;
        if (k == 0)
            return (0);
    } while (k != t);
    return (vertex[t].label);
}
void short_path(int v)
{
    int a, i, u, l = 0;
    int pred[50];
    static int path[50]; // Shortest Path array
    u = v;
    for (u = END; u != 0; u = vertex[u].pred)
        path[++l] = u;
    for (i = l; i > 1; i--)
        out << path[i] << "->";
    out << END;
}