#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite LONG_MAX
#define initvalue 0
#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

void dijkstra(graphe *g, int n, int r);

int main(int argc, char **argv)
{
  graphe *g;
  char buf[256 * 40];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <filename>\n%s\n", argv[0], USAGE);
    exit(0);
  }

  g = ReadGraphe(argv[1]); /* lit le graphe a partir du fichier */

  dijkstra(g, g->nsom, 0);

  PlongementCirculaire(g, 300);    /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(g,                     /* genere une figure en PostScript */
            buf,                   // nom fichier
            1,                    // rayon sommets
            1,                     // taille fleches
            10,                    // marge
            0,                     // noms sommets
            0,                     // valeurs sommets
            0,                     // couleurs sommets
            0                      // valeurs arcs
  );

  TermineGraphe(g);

  return 0;
} /* main() */

/**
 * Find all the possible routes from a starting point using Dijkstra algorithm
 * @param{graphe} *g Graph (Pointer)
 * @param{int} n Length of Graph
 * @param{int} r Initial vertex
 * 
 * */
void dijkstra(graphe *g, int n, int r)
{

  Lifo *T;
  int i, s, k, mu, y, y_p, len, mini = 0;
  pcell p;
  boolean *S;
  int min = 0;

  T = CreeLifoVide(n);
  //S = EnsembleVide(n);

  int L[n];

  // Initialize the L array with infinite values
  // The idea is to start switching each value by the successors
  for (i = 0; i < n; i++)
  {
    L[i] = infinite;
    
    // We want to assure that only takes sucessors and not visited
    g->v_sommets[i] = -1;
  }

  // Initializing values
  LifoPush(T, r); // Putting the initial vertex r into the stack
  L[r] = initvalue; // Add the value 0 to the initial vertex
  k = initvalue; // Initiating counter
  g->v_sommets[r] = 0; // Putting the value 0 to the vertex
  int mm = initvalue; // MU Initiating weight (sum of the shortest path)

  while (k < n && mm != infinite)
  {
    printf("\n\n------------------------ Iteration %d \n", k);

    y = LifoPop(T);

    g->v_sommets[y] = 0;
    printf("\n\nORIGIN: %s", g->nomsommet[y]);

    printf("L[y]=%d and len=%d \n", L[y], len);
    mm = min(L[y], len); // Compare the length of the previous sucessors and the current stack value 
                         //to determine the next vertex to follow the sortest path

    // This Su[n] is used for count the minimun of sucessors for each iteration. 
    // The idea is that each iteration contains an array of zeros Su=[0,0,0,0,0,0]
    // And switching only the current sucessors to determine the minimum value
    // Here, the initialization
    int Su[n];
    for (i = 0; i < n; i++)
      {
        Su[i] = 0;
      }

    // For all the successors
    for (p = g->gamma[y]; p != NULL; p = p->next)
    {

      s = p->som; // s is the index of vertex
      len = p->v_arc; // len is the value of arc
      printf("\n\nDEST: %s", g->nomsommet[s]);

      printf("s %d ", s);
      printf("len %d \n", len);

      // Only checks non visited vertices
      if (g->v_sommets[s] == -1)
      {

        printf("mu=%d\n", mm);
        printf("SUMA=%d\n", mm + len);

        L[s] = mm + len; // Put into the main L array the values of the lengths
        Su[s] = L[s]; // Put into the temporal array Su to calculate the min between successors

        for (i = 0; i < n; i++){
          if(Su[i] != 0){ // Only take in account the existing values i.e different than 0
            // printf("MIN %d , %d =  %d \n",Su[i],Su[s],min(Su[i], Su[s]));
            len = min(Su[i], Su[s] + mm); // Find the minimum between the weights until this vertex (Su[s] + mm) and the current sucessors
          }
          
        }
                  
      }

      // printf("Su = [%d %d %d %d %d %d] \n", Su[0], Su[1], Su[2], Su[3], Su[4], Su[5]);
      //printf("L = [%d %d %d %d %d %d] \n", L[0], L[1], L[2], L[3], L[4], L[5]);
      LifoPush(T, s); // Push into the stack to update 
    }

    k++;

    //printf("S=[%d %d %d %d %d %d] \n ", S[0], S[1], S[2], S[3], S[4], S[5]);
  }

  printf("\n\n --------- END ------------------- \n");
  int rr;

  for (rr = 0; rr < n; rr++)
  {
    printf("L[%d] = %d", rr, L[rr]);
  }

  printf("\n");

  LifoTermine(T);// Finish the stack
}

