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
#include "dijkstra.h"
#include "shortest_path.h"

char *format_fi_g; 

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
graphe *SP(graphe *g, int x, int y, int *table_dijkstra)
{
  printf("\n\n************************************************");
  printf("\n\nYou depart from: %s", g->nomsommet[x]);
  printf("Your destination: %s \n\n", g->nomsommet[y]);
  printf("************************************************\n\n");

  graphe *g_1 = Symetrique(g);
  // copy_parameter_from_graph(g_1, g);
  graphe *g_f;
  boolean *D; /* pour les "descendants" (successeurs a N niveaux) */
  Lifo *S_P;  /* liste temporaire geree en pile (Last In, First Out) */
  int i, n, s, a;
  pcell p;
  char buf[256];

  n = g_1->nsom;
  S_P = CreeLifoVide(n);
  g_f = InitGraphe(g_1->nsom, g_1->narc);

  LifoPush(S_P, y);
  while (!LifoVide(S_P))
  {
    i = LifoPop(S_P);
    for (p = g_1->gamma[i]; p != NULL; p = p->next)
    { /* pour tout sommet s successeur de i */
      s = p->som;
      a = p->v_arc;

      if (table_dijkstra[i] >= table_dijkstra[s] + a)
      {
        AjouteArcValue(g_f, s, i, a);
        printf("----- Station: %s", g->nomsommet[i]);
        LifoPush(S_P, s);
      }
    }
  }

  
  LifoTermine(S_P);

  // copy_parameter_from_graph(g_f, g);
  // plot_graph(g_f,buf,buf);

  return g_1;
}

// Copy information from one graph to another
void copy_parameter_from_graph(graphe *dest, graphe *src)
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

void plot_graph(graphe *g, char *buf, char *format_fi)
{
  // Plotting
  // PlongementCirculaire(g, 150);    /* plonge le graphe dans le plan */
  sprintf(buf, "ca-%s.eps", format_fi_g); /* construit le nom du fichier PostScript */
  EPSGraphe(g,                     /* genere une figure en PostScript */
            buf,                     // nom fichier
            2,                       // rayon sommets
            3,                       // taille fleches
            50,                      // marge
            1,                       // noms sommets
            0,                       // valeurs sommets
            1,                       // couleurs sommets
            1                        // valeurs arcs
  );
}

// void get_format_fi(char *format_fi){
//   format_fi_g = format_fi;
// }