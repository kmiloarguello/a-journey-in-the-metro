#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite LONG_MAX
#define initvalue 0
#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

graphe *dijkstra(graphe *g, int r, int t);
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

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  printf("\n\nEnter the destination vertex: ");
  scanf("%d", &final_vertex);
    
  gf = dijkstra(g, initial_vertex, final_vertex);

  PlongementCirculaire(gf, 300);   /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(gf,                    /* genere une figure en PostScript */
            buf,                   // nom fichier
            1,                     // rayon sommets
            1,                     // taille fleches
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
 * @param{int} r a vertex of g.
 * @brief compute, for each vertex y of g, the length Dx(y)of a shortest path
 *        from x to y. This length is stored in the field 
 *        v_sommets of the structure g.
 * 
 **/
graphe *dijkstra(graphe *g, int r, int t)
{
  Lifo *T;
  int i, s, k, y, next_vertex, y_p, len, mini = 0;
  int min = 0;
  int n = g->nsom;
  int a, b;
  pcell p;
  //boolean *S;
  //boolean duplicated = FALSE; // Helps to prevents previous vertices

  T = CreeLifoVide(n);

  int L[n]; // Array of all the distances between all the vertex starting from r

  // Initialize the L array with infinite values
  // The idea is to start switching each value by the successors
  for (i = 0; i < n; i++)
  {
    L[i] = infinite;
    // We want to assure that only takes sucessors and not visited
    g->v_sommets[i] = -1;
  }

  // Initializing values
  LifoPush(T, r);      // Putting the initial vertex r into the stack
  L[r] = initvalue;    // Add the value 0 to the initial vertex
  k = initvalue;       // Initiating counter
  g->v_sommets[r] = 0; // Putting the value 0 to the vertex
  int mm = initvalue;  // MU Initiating weight (sum of the shortest path)

  printf("\n\n************************************************");
  printf("\n\nYou depart from: %s", g->nomsommet[r]);
  printf("Your destination: %s \n\n", g->nomsommet[t]);
  printf("************************************************\n\n");

  while (k < n && mm != infinite)
  {
    printf("\n\n------------------------ Iteration %d \n", k);
    // This Su[n] is used for count the minimun of sucessors for each iteration.
    // The idea is that each iteration contains an array of zeros Su=[0,0,0,0,0,0]
    // And switching only the current sucessors to determine the minimum value
    // Here, the initialization
    int Su[n];
    for (i = 0; i < n; i++)
    {
      Su[i] = infinite;
    }

    y = LifoPop(T);

    // We need to assure than there is not previous values equals
    // That's mean no vertices with the same value than other
    // This checks runs in O(n^2)
    // for (a = 0; a < n; a++)
    // {
    //   for (b= a + 1; b <n; b++){
    //     if(L[a] == L[b] && L[a] != infinite){
    //       printf("It's impossible find the destination.\n");
    //       duplicated = TRUE;
    //       break;
    //     }
    //   }
    // }
    // if(duplicated) break;

    printf("\n\nORIGIN: %s", g->nomsommet[y]);
    printf("Vertex %d ", y);
    // printf("s=%d len=%d and t=%d \n", s, len, t);

    g->v_sommets[y] = 0;
    mm = min(L[y], len); // Compare the length of the previous sucessors and the current stack value
                         //to determine the next vertex to follow the sortest path

    if (t == y)
    {
      printf("\n\n************************************************");
      printf("\n\nYou arrived: %s \n\n", g->nomsommet[y]);
      printf("************************************************\n\n");
      break;
    }

    if (g->gamma[y] == NULL)
      break;

    // For all the successors
    for (p = g->gamma[y]; p != NULL; p = p->next)
    {

      s = p->som;     // s is the index of vertex
      len = p->v_arc; // len is the value of arc

      printf("\n\nNEXT: %s", g->nomsommet[s]);
      printf("Vertex %d ", s);
      printf("Distance: %d \n", len);

      // Only checks non visited vertices
      if (g->v_sommets[s] == -1)
      {

        printf("mu=%d\n", mm);
        printf("SUMA=%d\n", mm + len);

        L[s] = mm + len; // Put into the main L array the values of the lengths
        Su[s] = len;     // Put into the temporal array Su to calculate the min between successors

        // Defining the minimum of sucessors
        int ii, arc_min = 0; // arc_min contains the value of the minimum arc

        arc_min = Su[0]; // We suppose that the first arc is the minimum

        // Check if the previous arc_min is the minimum value
        // If there is another one lower update arc_min
        for (ii = 1; ii < n; ii++)
        {
          if (Su[ii] < arc_min)
          {
            arc_min = Su[ii];
          }
        }

        // After founded the minimum, just check that is a correct successor
        // And update the index of next vertex which later will be pushed into the stack
        if (arc_min == len)
        {
          next_vertex = s;
        }

        LifoPush(T, next_vertex); // Push into the stack to update
      }
    }

    k++;
  }

  printf("\n\n --------- END ------------------- \n");
  int rr, counter_path = 0;

  for (rr = 0; rr < n; rr++)
  {
    // if (L[rr] != infinite)
    // {
    printf("L[%d] = %d Station: %s", rr, L[rr], g->nomsommet[rr]);
    // counter_path += 1;
    // }
  }

  // int Lf[counter_path];

  //printf("%ld", sizeof(counter_path));
  // graphe *g_1;

  // int n_vert, n_arcs, e, f;
  // pcell pc;

  // n_vert = counter_path;
  // n_arcs = counter_path;
  // //n_arcs = counter_path;

  // g_1 = InitGraphe(n_vert, n_arcs);

  // for (e = 0; e < n_vert; e++) /* pour tout i sommet de g */
  // {
  //   for (pc = g->gamma[i]; pc != NULL; pc = pc->next)
  //   { /* pour tout j successeur de i */
  //     f = pc->som;
  //     AjouteArcValue(g_1, j, i, p->v_arc);
  //   } // for p
  // } // for i

  LifoTermine(T); // Finish the stack

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
