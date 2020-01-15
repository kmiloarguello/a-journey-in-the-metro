
#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"
#include "dijkstra.h"
#include "shortest_path.h"

#define infinite LONG_MAX

/**
 * Find all the possible routes from a starting point using Dijkstra algorithm
 * \fn void Dijkstra(graphe * g, int x)
 * @param{graphe} *g a network. The length of each arc must be stored in 
 *                    the field v_arc of the structure cell.
 * @param{int} x a vertex of g.
 * @brief compute, for each vertex y of g, the length Dx(y)of a shortest path
 *        from x to y. This length is stored in the field 
 *        v_sommets of the structure g.
 * 
 **/
void dijkstra(graphe *g, int x, int *table_dijkstra)
{
  int i, k, vertex, y, arc, miu, min_y;
  boolean *S;
  int n = g->nsom;
  pcell p;

  S = EnsembleVide(n);
  int L[n];

  // Initialization
  for (y = 0; y < n; y++)
  {
    L[y] = infinite;
    S[y] = TRUE;
  }

  L[x] = 0;
  k = 0;
  miu = 0;
  y = x;

  while (k < n && miu != infinite)
  {

    // S[y] = FALSE;

    // Distance traversed or cost
    // miu = min(L[y], arc + miu);

    // if (g->gamma[y] == NULL)
    //   break;

    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      vertex = p->som;
      arc = p->v_arc;

      int sum = L[y] + arc;
      if(L[vertex] < infinite || L[vertex] >= sum){
        L[vertex] = sum;
      }

      // L[vertex] = arc + miu; // Assign the cost to the vertex
    }

    min_y = y;

    for(int i=0;i<n;i++){
      if(S[i] && S[i] != infinite && (L[i] < L[min_y])){
        min_y = i;
      }
    }

    S[y] = FALSE;
    y = min_y;

    // // Finds the minimum next value of y
    // // Helpers to find the minimum
    // int temp;
    // int d = 0;
    // int next_vertex; // Index of next vertex

    // for (int l = 0; l < n; l++)
    // {
    //   // TODO: This can be improved
    //   // Only taking the values beloging to the set S
    //   if (S[l] && L[l] != infinite)
    //   {
    //     // 1. Take one array position
    //     if (d == 0)
    //     {
    //       temp = L[l];
    //       next_vertex = l;
    //     }
    //     // 2. Compare the took version with the others
    //     // To find the minimum
    //     if (L[l] <= temp)
    //     {
    //       next_vertex = l;
    //     }

        // Counter increments until the next posible vertex is selected
    //     d++;
    //   }
    // }

    // y = next_vertex;
    k++;
  }

  print_dijkstra(L, n);
  table_dijkstra = L;
  // ask_vertices(g,table_dijkstra);
}

void print_dijkstra(int *table_dijkstra, int n)
{
  printf("\n\n ------------ DIJKSTRA ------------------- \n");
  printf(" L[");
  for (int i = 0; i < n; i++)
  {
    printf(" %d ", table_dijkstra[i]);
  }
  printf("]");
  printf("\n ------------ END DIJKSTRA ------------------- \n");
}

void ask_vertices(graphe *g, int *table_dijkstra){
  int initial_vertex, final_vertex;

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  printf("\n\nEnter the destination vertex: ");
  scanf("%d", &final_vertex);

  SP(g, initial_vertex, final_vertex, table_dijkstra);
  // printf("HEY\n");
}
