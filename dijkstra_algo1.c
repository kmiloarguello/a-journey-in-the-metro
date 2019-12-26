#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite 1000000

#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

void dijkstra(graphe *g, int n, int r);
int ca_min(int a, int b);

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

  dijkstra(g, g->nsom, 0);

  PlongementCirculaire(g, 150);    /* plonge le graphe dans le plan */
  sprintf(buf, "%s.eps", argv[1]); /* construit le nom du fichier PostScript */
  EPSGraphe(g,                     /* genere une figure en PostScript */
            buf,                   // nom fichier
            10,                    // rayon sommets
            5,                     // taille fleches
            60,                    // marge
            0,                     // noms sommets
            1,                     // valeurs sommets
            1,                     // couleurs sommets
            1                      // valeurs arcs
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
  int i, s, k, mu, y, y_p, len;
  pcell p;
  boolean *S;

  T = CreeLifoVide(n);
  S = EnsembleVide(n);

  int L[n];

  for (i = 0; i < n; i++)
  {
    L[i] = infinite;
    S[i] = TRUE;
  }

  LifoPush(T, r);
  //g->v_sommets[r] = 0;
  L[r] = 0;
  k = 0;
  mu = 0;
  /*
  printf("------------------------ INIT  \n");
  printf("------------------------ INIT  \n");
  printf("------------------------ INIT  \n");
  printf("k = %d \n", k);
  printf("mu = %d \n", mu);
  printf("L = [%d %d %d %d %d %d] \n", L[0],L[1],L[2],L[3],L[4],L[5]);
*/
  while (k < n && mu != infinite)
  {
    //printf("------------------------ Iteration %d \n",k);
    y = LifoPop(T);
    y_p = y;
    S[y] = FALSE;
    L[y_p] = ca_min(L[y], y);
    k++;

    mu = L[y_p];

    printf("y %d \n", y);
    //printf("mu %d \n",mu);
    //printf("CA %d %d %d %d %d %d ", CA[0],CA[1],CA[2],CA[3],CA[4],CA[5]);
    //printf("L = [%d %d %d %d %d %d] \n", L[0],L[1],L[2],L[3],L[4],L[5]);

    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      s = p->som;
      len = p->v_arc;

      //printf("HOLA %d \n", S[s] );

      if (S[s] == TRUE)
      {
        L[s] = len;
        L[y] = ca_min(L[s], L[y_p] + len);
      }

      //printf("y %d \n",y);
      //printf("s %d \n",s);
      //printf("len %d \n",len);

      //printf("S %d %d %d %d %d %d ", S[0],S[1],S[2],S[3],S[4],S[5]);

      /*
      for(i=0;i<n;i++){
	L[k] = ca_min(L[k],L[i]);
        L[k] = ca_min(L[k], L[y_p] + len);
      }
      */

      //printf("L = [%d %d %d %d %d %d] \n", L[0],L[1],L[2],L[3],L[4],L[5]);
      LifoPush(T, s);
    }
  }

  /*
  printf("\n\n --------- END ------------------- \n");
  int rr;

  for(rr=0;rr<n;rr++){
	printf("L[%d] = %d \n",rr,L[rr]);
  } 
*/
  LifoTermine(T);
}

int ca_min(int a, int b)
{
  if (a <= b)
  {
    return a;
  }
  else
  {
    return b;
  }
}
