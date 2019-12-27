#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite 1000000
#define initvalue 0
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
            1,                     // noms sommets
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
  int i, s, k, mu, y, y_p, len, mini = 0;
  pcell p;
  boolean *S;
  int min = 0;

  T = CreeLifoVide(n);
  //S = EnsembleVide(n);

  int L[n];

  for (i = 0; i < n; i++)
  {
    L[i] = infinite;
    //S[i] = TRUE;
    g->v_sommets[i] = -1;
  }

  LifoPush(T, r);

  L[r] = initvalue;
  k = initvalue;
  mu = initvalue;
  g->v_sommets[r] = 0;
  int mm = 0;

  while (k < n && mu != infinite)
  {
    printf("\n\n------------------------ Iteration %d \n", k);

    y = LifoPop(T);

    g->v_sommets[y] = 0;
    printf("\n\nN: %s", g->nomsommet[y]);

    printf("L[y]=%d and len=%d \n", L[y], len);
    mm = min(L[y], len);

    int Su[n];
    for (i = 0; i < n; i++)
      {
        Su[i] = 0;
      }

    for (p = g->gamma[y]; p != NULL; p = p->next)
    {

      s = p->som;
      len = p->v_arc;
      printf("\n\nVertex: %s", g->nomsommet[s]);

      printf("s %d ", s);
      printf("len %d \n", len);

      if (g->v_sommets[s] == -1)
      {

        printf("mu=%d\n", mm);
        printf("SUMA=%d\n", mm + len);

        L[s] = mm + len;

        Su[s] = L[s];

        for (i = 0; i < n; i++){
          if(Su[i] != 0){
            printf("MIN %d , %d =  %d \n",Su[i],Su[s],min(Su[i], Su[s]));
            len = min(Su[i], Su[s] + mm);
          }
          
        }
                  
      }

      printf("Su = [%d %d %d %d %d %d] \n", Su[0], Su[1], Su[2], Su[3], Su[4], Su[5]);
      printf("L = [%d %d %d %d %d %d] \n", L[0], L[1], L[2], L[3], L[4], L[5]);
      LifoPush(T, s);
    }

    k++;

    //printf("S=[%d %d %d %d %d %d] \n ", S[0], S[1], S[2], S[3], S[4], S[5]);
  }

  // printf("\n\n --------- END ------------------- \n");
  // int rr;

  // for (rr = 0; rr < n; rr++)
  // {
  //   printf("L[%d] = %d \n", rr, L[rr]);
  // }

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
