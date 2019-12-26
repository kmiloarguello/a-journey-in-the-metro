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
 * 
 * @param{graphe} *g Graph (Pointer)
 * @param{int} n Length of Graph
 * @param{int} r Initial vertex
 * 
 * */
void dijkstra(graphe *g, int n, int r)
{

  Lifo *S;
  int i, s, k, mu, y, y_p, len;
  pcell p;

  S = CreeLifoVide(n);

  int L[n];

  //for(i=0;i<n;i++){
  //	L[i] = infinite;
  /*for (p = g->gamma[i]; p != NULL; p = p->next)
 	{ 
      		s = p->som;
		len = p->v_arc;
		//printf("%d\n ",len);
      		LifoPush(S,s);
    	}*/

  //}

  LifoPush(S, r);
  //g->v_sommets[r] = 0;
  //L[r] = 0;
  //k = 0;
  //mu = 0;

  while (k < n && mu != infinite)
  {
    //printf("------------------------ Iteration %d \n",k);
    y = LifoPop(S);
    //L[y_p] = ca_min(L[y], y);

    k++;
    //mu = L[y_p];
    //printf("L[y_p] %d \n",L[y_p]);
    //printf("mu %d \n",mu);
    for (p = g->gamma[y]; p != NULL; p = p->next)
    {
      s = p->som;
      len = p->v_arc;

      //printf("s %d \n",s);
      //printf("len %d \n",len);

      //L[y] = min(L[y], L[y_p] + len);
      //printf("L[y] = %d \n",y,L[y]);
      LifoPush(S, s);
    }
  }
  /*
  int rr;

  for(rr=0;rr<n;rr++){
	printf("L[%d] = %d \n",rr,L[rr]);
  } */

  LifoTermine(S);
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
