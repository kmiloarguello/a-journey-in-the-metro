/**
 * Graph & Algorithms Course
 * ESIEE Paris
 * 2019
 * 
 * Student: ARGUELLO Camilo
 * 
 * This code calculates the shortest path for a given graph.
 * */

#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite LONG_MAX
#define initvalue 0
#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

int *table_dijkstra;
graphe *final_graph;
void dijkstra(graphe *g, int x);
graphe *SP(graphe *g, int x, int y);
int destination;

// Helpers functions
graphe *init_shortest_path(graphe *g);

int main(int argc, char **argv)
{
  graphe *g;
  char buf[256];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]); /* lit le graphe a partir du fichier */

  init_shortest_path(g);

  PlongementCirculaire(final_graph, 150);    /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(final_graph,                     /* genere une figure en PostScript */
            buf,                   // nom fichier
            2,                     // rayon sommets
            3,                     // taille fleches
            50,                    // marge
            1,                     // noms sommets
            0,                     // valeurs sommets
            1,                     // couleurs sommets
            1                      // valeurs arcs
  );

  TermineGraphe(g);
  TermineGraphe(final_graph);
  return 0;
} /* main() */

/**
 * Ask the initial and final vertex to the user
 * Then, Load SP() function
 * */
graphe *init_shortest_path(graphe *g)
{

  graphe *gf;

  int initial_vertex, final_vertex;

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  printf("\n\nEnter the destination vertex: ");
  scanf("%d", &final_vertex);

  gf = SP(g, initial_vertex, final_vertex);

  return gf;
}

/* ====================================================================== */
/*! \fn graphe * SP(graphe * g, int x, int y)
    \param g (entrée) : a network. The length of each arc must be stored in
                        the field v_arc of the structure cell.
    \param x (entrée) : a vertex of g (start).
    \param y (entrée) : a vertex of g (arrival).
    \return a shortest path from x to y in g.
    \brief returns a shortest path from x to y in g.
*/
/* ====================================================================== */
graphe *SP(graphe *g, int x, int y)
{

  printf("\n\n************************************************");
  printf("\n\nYou depart from: %s", g->nomsommet[x]);
  printf("Your destination: %s \n\n", g->nomsommet[y]);
  printf("************************************************\n\n");

  destination = y;

  dijkstra(g, x);

  // int arc, ver, n;
  // n = g->nsom;
  // pcell p;

  // for (int i = 0; i < n; i++)
  // {
  //   for (p = g->gamma[i]; p != NULL; p = p->next)
  //   {
  //     arc = p->v_arc;
  //     ver = p->som;

  //     printf("vertex=%d and edge=%d and i=%d\n",ver,arc,i);
  // //   //   // if(arc == table_dijkstra[i]){

  // //   //   // }

  // //   // }

  // //   printf("Table[%d] = %d\n", i, table_dijkstra[i]);
  // //   // if (t == y)
  // //   // {
  // //   //   printf("\n\n************************************************");
  // //   //   printf("\n\nYou arrived: %s \n\n", g->nomsommet[y]);
  // //   //   printf("************************************************\n\n");
  // //   //   break;
  //   }
  // }

  // //RetireArc(g,1,2);

  return g;
}

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
void dijkstra(graphe *g, int x)
{
  int i, k, vertex, y, y_p, arc, miu, c;
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


  // For new graph
  int nsom = g->nsom;
  int narc = g->narc;
  final_graph = InitGraphe(nsom, narc);

  while (k < n && miu != infinite)
  {
    S[y] = FALSE;
    printf("Station: %s", g->nomsommet[y]);

    // Distance traversed or cost
    miu = min(L[y], arc + miu);

    if (destination == y)
    {
      printf("\n\n************************************************");
      printf("\n\nYou arrived: %s \n\n", g->nomsommet[y]);
      printf("************************************************\n\n");
      break;
    }

    if (g->gamma[y] == NULL)
      break;

    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      vertex = p->som;
      arc = p->v_arc;

      // Only for the non-visited vertices
      if (S[vertex])
      {
        L[vertex] = arc + miu;     // Assign the cost to the vertex
        miu = min(L[vertex], miu); // Update the cost
        AjouteArcValue(final_graph, y, vertex, arc);
      }
    }

    // Finds the minimum next value of y
    // Helpers to find the minimum
    int temp;
    int d = 0;
    int next_vertex; // Index of next vertex

    for (int l = 0; l < n; l++)
    {
      // TODO: This can be improved
      // Only taking the values beloging to the set S
      if (S[l] && L[l] != infinite)
      {
        // 1. Take one array position
        if (d == 0)
        {
          temp = L[l];
          next_vertex = l;
        }
        // 2. Compare the took version with the others
        // To find the minimum
        if (L[l] <= temp)
        {
          next_vertex = l;
        }

        // Counter increments until the next posible vertex is selected
        d++;
      }
    }

    y = next_vertex;
    k++;
  }

  printf("\n\n ------------ DIJKSTRA ------------------- \n");
  int rr;

  for (rr = 0; rr < n; rr++)
  {
    printf("L[%d] = %d\n", rr, L[rr]);
  }

  table_dijkstra = L;
}