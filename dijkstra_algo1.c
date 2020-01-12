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

graphe *dijkstra(graphe *g, int x);
graphe *SP(graphe *g, int x, int y);

int main(int argc, char **argv)
{
  graphe *g;
  graphe *gf;
  char buf[256 * 40];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]); /* lit le graphe a partir du fichier */

  int initial_vertex, final_vertex;

  // printf("\n\nEnter the initial vertex: ");
  // scanf("%d", &initial_vertex);

  // printf("\n\nEnter the destination vertex: ");
  // scanf("%d", &final_vertex);

  gf = dijkstra(g, 0);

  PlongementCirculaire(gf, 300);   /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(gf,                    /* genere une figure en PostScript */
            buf,                   // nom fichier
            1,                     // rayon sommets
            3,                     // taille fleches
            10,                    // marge
            1,                     // noms sommets
            0,                     // valeurs sommets
            0,                     // couleurs sommets
            1                      // valeurs arcs
  );

  TermineGraphe(g);

  return 0;
} /* main() */

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
graphe *dijkstra(graphe *g, int x)
{
  int i, k, vertex, y, y_p, arc, miu, c;
  boolean *S;
  int n = g->nsom;
  pcell p;

  S = EnsembleVide(n);
  int L[n];

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
    printf("\n\n------------------------ Iteration %d \n", k);
    S[y] = FALSE;

    printf("\n\nORIGIN: %s", g->nomsommet[y]);
    printf("Vertex %d ", y);

    miu = min(L[y] , arc + miu);

    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      vertex = p->som;
      arc = p->v_arc;

      if(S[vertex]){
        printf("\n\nNEXT: %s", g->nomsommet[vertex]);
        printf("Vertex %d ", vertex);
        printf("Distance: %d \n", arc);
        printf("Miu: %d \n", miu);
      
        L[vertex] = arc + miu;
        miu = min(L[vertex],miu);

        printf("L[%d]=%d \n",y,L[y]);

        

      }

    }
    printf("y=%d, L=[%d %d %d %d %d %d] \n", y, L[0], L[1], L[2], L[3], L[3], L[4]);
    printf("S=[%d %d %d %d %d %d]\n",S[0],S[1],S[2],S[3],S[3],S[4]);

    // Helpers to find the minimum
    int temp;
    int d=0;
    int next_vertex; // Index of next vertex

    for (int l = 0; l < n; l++)
    {
      // Only taking the values beloging to the set S
      if (S[l] && L[l] != infinite)
      {
        if (d == 0){
          temp = L[l];
          next_vertex = l;
        }
        
        if(L[l] < temp){
          next_vertex = l;
        }

        d++;

      }
    }
    y = next_vertex;
    k++;
  }
  /*
    printf("\n\n --------- END ------------------- \n");
  int rr;

  for (rr = 0; rr < n; rr++)
  {
    printf("L[%d] = %d Station: %s", rr, L[rr], g->nomsommet[rr]);
  }

  */

  // printf("Done");

  return g;
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
  return g;
}
