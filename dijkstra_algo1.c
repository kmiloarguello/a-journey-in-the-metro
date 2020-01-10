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

  printf("\n\nEnter the initial vertex: ");
  scanf("%d", &initial_vertex);

  // printf("\n\nEnter the destination vertex: ");
  // scanf("%d", &final_vertex);
    
  gf = dijkstra(g, initial_vertex);

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
 * @param{int} r a vertex of g.
 * @param{int} t is the destination vertex.
 * @brief compute, for each vertex y of g, the length Dx(y)of a shortest path
 *        from x to y. This length is stored in the field 
 *        v_sommets of the structure g.
 * 
 **/
graphe *dijkstra(graphe *g, int x)
{
  int i, k, y,y_p, mmu;
  boolean* S;
  int n = g->nsom;
  pcell p;

  S = EnsembleVide(n);
  int L[n];

  for(y=0;y<n;y++){
    L[y] = infinite;
    S[y] = TRUE;
  }

  L[x] = 0;
  k = 0;
  mmu = 0;

  while(k < n && mmu != infinite){

    printf("%d %d ", y , L[y]);

    S[y] = FALSE;

    y_p = S[y];
    L[y_p] = min(L[y],y);
    k++;
    mmu=L[y_p];
    
    for (p = g->gamma[y_p]; p != NULL; p = p->next)
    {
      if(S[y_p] == TRUE){
        L[y_p] = min(L[y], L[y_p] + p->v_arc);
      }
      
      //printf("L[y_p] = %d\n", L[y_p]);
    }
  }

  

 // printf("Done");





//   Lifo *T;
//   int i, s, k, y, next_vertex, y_p, len, mini = 0;
//   int min = 0;
//   int n = g->nsom;
//   int a, b;
//   pcell p;
//   //boolean *S;
//   //boolean duplicated = FALSE; // Helps to prevents previous vertices

//   T = CreeLifoVide(n);

//   int L[n]; // Array of all the distances between all the vertex starting from r

//   // Initialize the L array with infinite values
//   // The idea is to start switching each value by the successors
//   for (i = 0; i < n; i++)
//   {
//     L[i] = infinite;
//     // We want to assure that only takes sucessors and not visited
//     // add i into T
//     LifoPush(T, i);
//     //   g->v_sommets[i] = -1;
//   }

//   // Initializing values
//   // LifoPush(T, r);      // Putting the initial vertex r into the stack
//   L[r] = initvalue;    // Add the value 0 to the initial vertex
//   k = initvalue;       // Initiating counter
//  //  g->v_sommets[r] = 0; // Putting the value 0 to the vertex
//   int mm = initvalue;  // MU Initiating weight (sum of the shortest path)

//   printf("\n\n************************************************");
//   printf("\n\nYou depart from: %s", g->nomsommet[r]);
//   printf("Your destination: %s \n\n", g->nomsommet[t]);
//   printf("************************************************\n\n");

//   while (k < n && mm != infinite)
//   {
//     printf("\n\n------------------------ Iteration %d \n", k);
//     // This Su[n] is used for count the minimun of sucessors for each iteration.
//     // The idea is that each iteration contains an array of zeros Su=[0,0,0,0,0,0]
//     // And switching only the current sucessors to determine the minimum value
//     // Here, the initialization
//     int Su[n];
//     for (i = 0; i < n; i++)
//     {
//       Su[i] = infinite;
//     }

//     y = LifoPop(T);
//     g->v_sommets[y] = 0;
//     mm = min(L[y], mm + len); // Compare the length of the previous sucessors and the current stack value
//                          //to determine the next vertex to follow the sortest path

//     printf("MM=%d", mm);
    
//     printf("\n\nORIGIN: %s", g->nomsommet[y]);
//     printf("Vertex %d ", y);

//     if (t == y)
//     {
//       printf("\n\n************************************************");
//       printf("\n\nYou arrived: %s \n\n", g->nomsommet[y]);
//       printf("************************************************\n\n");
//      // break;
//     }

//     if (g->gamma[y] == NULL)
//       break;

//     // For all the successors
//     for (p = g->gamma[y]; p != NULL; p = p->next)
//     {

//       s = p->som;     // s is the index of vertex
//       len = p->v_arc; // len is the value of arc

//       printf("\n\nNEXT: %s", g->nomsommet[s]);
//       printf("Vertex %d ", s);
//       printf("Distance: %d \n", len);

//       // Only checks non visited vertices
//       if (g->v_sommets[s] == -1)
//       {

//         printf("mu=%d\n", mm);
//         printf("SUMA=%d\n", mm + len);

//         L[s] = mm + len; // Put into the main L array the values of the lengths
//         Su[s] = len;     // Put into the temporal array Su to calculate the min between successors

//         // Defining the minimum of sucessors
//         int ii, arc_min = 0; // arc_min contains the value of the minimum arc

//         arc_min = Su[0]; // We suppose that the first arc is the minimum

//         // Check if the previous arc_min is the minimum value
//         // If there is another one lower update arc_min
//         for (ii = 1; ii < n; ii++)
//         {
//           if (Su[ii] < arc_min)
//           {
//             arc_min = Su[ii];
//           }
//         }

//         // After founded the minimum, just check that is a correct successor
//         // And update the index of next vertex which later will be pushed into the stack
//         // TODO: Here I am just checking the values of successor, and compared with the minimum arc. 
//         //       The goal is compare the sum of all the values until here with something else 
//         if (arc_min == len)
//         {
//           next_vertex = s;
//         }

//         LifoPush(T, next_vertex); // Push into the stack to update
//       }
//     }

//     k++;
//   }

//   printf("\n\n --------- END ------------------- \n");
//   int rr;

//   for (rr = 0; rr < n; rr++)
//   {
//     printf("L[%d] = %d Station: %s", rr, L[rr], g->nomsommet[rr]);
//   }



//   LifoTermine(T); // Finish the stack

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
