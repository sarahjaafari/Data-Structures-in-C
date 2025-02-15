/*
 -------------------------------------
 File:    edgelist.h
 Project: a10
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-04-03
 -------------------------------------
 */
#ifndef EDGELIST_H_
#define EDGELIST_H_

/*
 * Define structure EDGE if linked list node
 * from  - index of source vertex
 * to - index of destination vertex
 * weight - weight of the edge
 * next  - pointer to the next edge node
 */
typedef struct edgenode {
	int from;
	int to;
	int weight;
	struct edgenode *next;
} EDGENODE;

/*
 * Define structure EDGELIST of edge list graph DS
 * size  - number of edges
 * start - pointer to the first edge node
 * end   - pointer to the last edge node
 */
typedef struct edgelist {
	int size;
	EDGENODE *start;
	EDGENODE *end;
} EDGELIST;

/* Create and return a new edge list graph*/
EDGELIST* new_edgelist();

/* Add a new edge at the start of the linked list of edges*/
void insert_edge_start(EDGELIST *g, int from, int to, int weight);

/* Add an new edge at the end of the linked list of edges */
void insert_edge_end(EDGELIST *g, int from, int to, int weight);

/* Delete edge (from to) from the edgelist */
void delete_edge(EDGELIST *g, int from, int to);

/* Get the weight of the graph */
int weight_edgelist(EDGELIST *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp);

/* Display edge list graph*/
void display_edgelist(EDGELIST *g);

#endif /* EDGELIST_H_ */
