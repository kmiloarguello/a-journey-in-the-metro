/**
 * Graph & Algorithms Course
 * ESIEE Paris
 * 2019
 * 
 * Student: ARGUELLO Camilo
 * 
 * This code calculates the shortest path for a given graph.
 * The input must contain the graph structure with names,values and arcs.
 * The code was tested with test_dijkstra.graph file and metro_complete.graph file (in the same folder).
 * 
 ***** Order of execution by functions. *****
 *      [MAIN] -> [DIJKSTRA] -> [SP]
 *
 *(1) It asks to the user to indicate the start vertex X.
 *(2) Then, it calculates Dijkstra.
 *(3) Then, it asks to the user to type the second vertex value Y.
 *(4) Then, it finds the Shortest Path from X to Y.
 *(5) Finally, it prints the results in *.eps file and in the console.
 *
 * */

#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite LONG_MAX
#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

void dijkstra(graphe *g, int x);
void print_dijkstra(int *table_dijkstra, int n);
graphe *SP(graphe *g, int x, int y);
void assign_graph_parameters(graphe *dest, graphe *src);

// Helpers variables
int *table_dijkstra;
int initial_vertex, final_vertex;
char *format_fi;

int main(int argc, char **argv)
{
  graphe *g;
  
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]); /* lit le graphe a partir du fichier */

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  format_fi = argv[1];
  dijkstra(g, initial_vertex);

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
void dijkstra(graphe *g, int x)
{
  int i, k, vertex, y, arc, miu;
  int minimum, temporal, min_y;
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
    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      vertex = p->som;
      arc = p->v_arc;

      // Find the minimum next value if corresponds
      L[vertex] = (L[vertex] < L[y] + arc) ? L[vertex] : L[y] + arc;
    }

    minimum = infinite;
    min_y = 0;

    for (int i = 0; i < n; i++)
    {
      if (S[i] && S[i] != infinite)
      {
        temporal = L[i];

        if (temporal < minimum)
        {
          minimum = temporal;
          min_y = i;
        }
      }
    }

    miu = minimum; // Distance traversed or cost
    y = min_y;     // Next minimum index vertex
    S[y] = FALSE;  // Vertex visited assigned to false

    k++;
  }

  print_dijkstra(L, n);
  table_dijkstra = L;

  printf("\n\nEnter the destination vertex: ");
  scanf("%d", &final_vertex);

  SP(g, initial_vertex, final_vertex);

}

/**
 * It shows the dijkstra table result
 * */
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

  int n, vertex, arc, new_x;
  n = g->nsom;
  graphe *g_2 = Symetrique(g);
  graphe *g_1 = InitGraphe(g->nsom, g->narc);
  pcell p;

  // Helper variables in order to print and plot
  int a = x;
  int b = y;

  // We start from the last vertex in backtrack to find and construct the new graph
  while (x != y)
  {
    for (p = g_2->gamma[y]; p != NULL; p = p->next)
    {
      vertex = p->som;
      arc = p->v_arc;

      // Compare i.e the last vertex with the predecesor. 
      // We need to confirm that the arc selected is on on the dijkstra result
      if (table_dijkstra[y] - table_dijkstra[vertex] == arc)
      {
        AjouteArcValue(g_1, vertex, y, arc);
        y = vertex;
      }
    }
  }

  g_1 = Symetrique(g_1);
  TermineGraphe(g_2);
  assign_graph_parameters(g_1, g);

  int v;
  pcell p1;

  printf("\n\n************************************************");
  printf("\n\nYou depart from: %s", g->nomsommet[a]);
  for (int i = 0; i < n; i++)
  {
    for (p1 = g_1->gamma[i]; p1 != NULL; p1 = p1->next)
    {
      v = p1->som;

      if(v != b) printf("\n[NEXT] Station: %s", g_1->nomsommet[v]);

    } 
  } 
  printf("\nYour destination: %s", g->nomsommet[b]);
  printf("\n************************************************\n");

  // Plotting
  char buf[256];

  sprintf(buf, "%s_ca.eps", format_fi); /* construit le nom du fichier PostScript */
  EPSGraphe(g_1,                     /* genere une figure en PostScript */
	    buf, // nom fichier
	    3,  // rayon sommets
	    1,   // taille fleches
	    60,  // marge
	    0,   // noms sommets
	    0,   // valeurs sommets
	    1,   // couleurs sommets
	    0    // valeurs arcs
	    );
  

  return g_1;
}

/**
 * To prevent errors when plotting, it is helpful to copy all the values from the current graph to the new one
 * */
void assign_graph_parameters(graphe *dest, graphe *src)
{
  int i;
  int l;

  dest->x = (double *)malloc(src->nsom * sizeof(double));
  memcpy(dest->x, src->x, src->nsom * sizeof(double));

  dest->y = (double *)malloc(src->nsom * sizeof(double));
  memcpy(dest->y, src->y, src->nsom * sizeof(double));

  dest->v_arcs = (long int *)malloc(src->nmaxarc * sizeof(TYP_VARC));
  memcpy(dest->v_arcs, src->v_arcs, src->nmaxarc * sizeof(TYP_VARC));

  dest->v_sommets = (long int *)malloc(src->nsom * sizeof(TYP_VSOM));
  memcpy(dest->v_sommets, src->v_sommets, src->nsom * sizeof(TYP_VSOM));

  dest->nomsommet = (char **)malloc(src->nsom * sizeof(char *));
  for (i = 0; i < src->nsom; i++)
  {
    l = strlen(src->nomsommet[i]);
    dest->nomsommet[i] = (char *)malloc((l + 1) * sizeof(char));
    memcpy(dest->nomsommet[i], src->nomsommet[i], (l + 1) * sizeof(char));
  }
}