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
void dijkstra(graphe *g, int x);
graphe *SP(graphe *g, int x, int y);

// Helpers functions
void ask_user_vertices(graphe *g);

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

  dijkstra(g, 3);
//   graphe *g_1 = Symetrique(g);

//   int arc, ver_1,arc_1, ver, n_1,n;
//   n_1 = g_1->nsom;
//   n= g->nsom;
//   pcell p_1,p;

//   for (int i = 0; i < n_1; i++)
//   {
//       // printf("name=%s", g_1->nomsommet[1]);
//     printf("Vertex %d\n",i);
//     for (p_1 = g_1->gamma[i]; p_1 != NULL; p_1 = p_1->next)
//     {
//       arc_1 = p_1->v_arc;
//       ver_1 = p_1->som;

//       printf("pre=%d\n", ver_1);
//     }
// printf("------------------\n");
// //     for (p = g->gamma[i]; p != NULL; p = p->next)
// //     {
// //       arc = p->v_arc;
// //       ver = p->som;

// //       printf("des=%d\n", ver);
// //     }

//   }

  PlongementCirculaire(g, 150);  /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(g,                   /* genere une figure en PostScript */
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
  return 0;
} /* main() */

/**
 * Ask the initial and final vertex to the user
 * Then, Load SP() function
 * */
void ask_user_vertices(graphe *g)
{

  int initial_vertex, final_vertex;

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  printf("\n\nEnter the destination vertex: ");
  scanf("%d", &final_vertex);

  SP(g, initial_vertex, final_vertex);
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

  graphe *g_1;

  g_1 = Symetrique(g);

  int arc, ver, n;
  n = g_1->nsom;
  pcell p;

  for (int i = 0; i < n; i++)
  {
    // printf("name=%s", g_1->nomsommet[0]);
    for (p = g_1->gamma[i]; p != NULL; p = p->next)
    {
      arc = p->v_arc;
      ver = p->som;

      printf("vertex=%d and edge=%d and i=%d\n", ver, arc, i);
    }
  }

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
  int i, k, vertex, y, arc, miu;
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
    S[y] = FALSE;

    // Distance traversed or cost
    miu = min(L[y], arc + miu);

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
  printf(" L[");
  for (int i = 0; i < n; i++)
  {
    printf(" %d ", L[i]);
  }
  printf("]");
  printf("\n ------------ END DIJKSTRA ------------------- \n");

  table_dijkstra = L;
  // ask_user_vertices(g);
}