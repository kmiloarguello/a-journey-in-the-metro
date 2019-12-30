#include <stdlib.h>
#include <stdio.h>
#include "graphaux.h"
#include "graphes.h"

#define infinite LONG_MAX
#define initvalue 0
#define USAGE "lit un graphe dans le fichier <filename> et genere une figure en PostScript dans <filename>.eps"

void dijkstra(graphe *g, int n, int r, int t);
graphe * SP(graphe *g, int x, int y);

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

  SP(g,0,203);

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
 * \fn void Dijkstra(graphe * g, int x)
 * @param{graphe} *g a network. The length of each arc must be stored in 
 *                    the field v_arc of the structure cell.
 * @param{int} r a vertex of g.
 * @brief compute, for each vertex y of g, the length Dx(y)of a shortest path
 *        from x to y. This length is stored in the field 
 *        v_sommets of the structure g.
 * 
 **/
void dijkstra(graphe *g, int r, int t)
{
  Lifo *T;
  int i, s, k, y, y_p, len, mini = 0;
  int min = 0;
  int n = g->nsom;
  int a,b;
  pcell p;
  boolean *S;
  boolean duplicated = FALSE; // Helps to prevents previous vertices

  T = CreeLifoVide(n);

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

    if(t == L[y]){
      printf("\n\nYou arrived: %s", g->nomsommet[y]);
      break;
    }

    // We need to assure than there is not previous values equals 
    // That's mean no vertices with the same value than other
    // This checks runs in O(n^2)
    for (a = 0; a < n; a++)
    {
      for (b= a + 1; b <n; b++){
        if(L[a] == L[b] && L[a] != infinite){
          printf("It's impossible find the destination.\n");
          duplicated = TRUE;
          break;
        }
      }     
    }
    if(duplicated) break;

    

    printf("\n\nORIGIN: %s", g->nomsommet[y]);
    printf("L[y]=%d and len=%d \n", L[y], len);

    g->v_sommets[y] = 0;
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

      printf("\n\nNEXT: %s", g->nomsommet[s]);
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
            len = min(Su[i], Su[s] + mm); // Find the minimum between the weights until this vertex (Su[s] + mu) and the current sucessors
          }
          
        }
                  
      }

      LifoPush(T, s); // Push into the stack to update 
    }

    k++;
  }

  printf("\n\n --------- END ------------------- \n");
  int rr;

  for (rr = 0; rr < ; rr++)
  {
    if(L[rr] != infinite){
      printf("Station: %s - L[%d] = %d\n", g->nomsommet[rr], rr, L[rr]);
    }
    
  }

  printf("\n");

  LifoTermine(T);// Finish the stack
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
graphe * SP(graphe *g, int x, int y){
  
  graphe *g_1;

  int nsom, narc, al_arcs, k, i, j;
  pcell p;

  dijkstra(g, x,y);

  nsom = g->nsom;
  narc = g->narc;
  g_1 = InitGraphe(nsom, narc);
  for (i = 0; i < nsom; i++) /* pour tout i sommet de g */
  {
    for (p = g->gamma[i]; p != NULL; p = p->next)
    { /* pour tout j successeur de i */
      j = p->som;
      AjouteArcValue(g_1, j, i, p->v_arc);
    } // for p
  } // for i

  return g_1;


}



