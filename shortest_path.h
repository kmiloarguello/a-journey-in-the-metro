#ifndef shortest_path_ca
#define shortest_path_ca

graphe *SP(graphe *g, int x, int y, int *table_dijkstra);
void copy_parameter_from_graph(graphe* dest, graphe* src);
void plot_graph(graphe *g, char *buf, char *format_fi);
// void get_format_fi(char *format_fi);

#endif
