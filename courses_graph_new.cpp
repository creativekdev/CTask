#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct adjacent_list
{
    int vertex;                 
    struct adjacent_list *next;
} * AdjList, *AdjListNodePtr, AdjListNode;




AdjList insert_vertex(AdjList adjList, int vertex)
{
    AdjListNodePtr cur = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    AdjListNodePtr nw = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    nw->vertex = vertex;
    nw->next = NULL;
    if (adjList)
    {
        cur = adjList;
        while (cur->next)
        {
            cur = cur->next;
        }
        cur->next = nw;
    }
    else
    {
       
        adjList = nw;
    }
    return adjList;
}


AdjList *construct_adjlist(const char *filename, AdjList *adjList, int *numVert)
{

    adjList = (AdjList *)calloc(60, sizeof(AdjList));
    FILE *ifp;
    int count = 0;
    if ((ifp = fopen(filename, "r")) == NULL)
    {
        printf("Invalid file name!");
        fflush(stdout);
        fclose(ifp);
        exit(EXIT_FAILURE);
    }
    char line[1024];
    while (fgets(line, sizeof line, ifp) != NULL)
    {
        int src_vertex, dst_vertex;
        char *pch;
        pch = strtok(line, " \n\r");
        sscanf(pch, "%d", &src_vertex);
        pch = strtok(NULL, " \n\r");
        while (pch != NULL)
        {
            sscanf(pch, "%d", &dst_vertex);
            adjList[src_vertex] = insert_vertex(adjList[src_vertex], dst_vertex);
            pch = strtok(NULL, " \n\r");
        }
        count++;
    }
    fclose(ifp);
    *numVert = count;
    return adjList;
}

void dfs_visit(int i, AdjList *graph, int numVer, int *color, int *result)
{
    static int cnt = 1;       // Keep track of the "time"
    AdjList hnode = graph[i]; // Extract the linked list of vertex i
    color[i] = 1;             // Update the color
    while (hnode)
    {
        int cur = hnode->vertex;       // current operating vertex
        if (color[hnode->vertex] == 1) // Check if the edge is a back edge
        {
            printf("This graph has a cycle!\n");
            exit(0);
        }
        if (color[hnode->vertex] == 0) // Explore the white vertex
        {
            // Recursion
            dfs_visit(hnode->vertex, graph, numVer, color, result);
        }
        // Proceed to the next node
        hnode = hnode->next;
    }
    // Update the color and the finish time
    color[i] = 2;
    result[cnt] = i;
    cnt += 1;
}

// DFS
void dfs(AdjList *graph, int numVer, int *result)
{
    int i;
    int *color;
    color = (int *)malloc((numVer + 1) * sizeof(int)); // Allocate the menory
    // Initialize all the vertices
    for (i = 1; i < numVer + 1; i++)
    {
        color[i] = 0;
    }
    for (i = 1; i < numVer + 1; i++)
    {
        // When the vertex is not explored
        if (color[i] == 0)
        {
            // Visit this vertex
            dfs_visit(i, graph, numVer, color, result);
        }
    }
}

// Find the largest element in an array
int largest(int arr[], int n)
{
    int i;
    int max = arr[1];
    for (i = 1; i < n + 1; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}



int main()
{
	char fileName[31];
	char c;
    printf("This program will read, from a file, a list of courses and their prerequesites and will print the list in which to take courses.\n");
    printf("Enter file name: ");
    scanf("%s%c", fileName, &c);
    
    AdjList *graph = NULL;
    int numVer;
    // Check input file

    graph = construct_adjlist(fileName, graph, &numVer); // Construct the adjacent list from input file
    int *result, *sortedArray;
    if (graph == NULL)
    {
        printf("invalid graph\n");
        exit(EXIT_FAILURE);
    }
    result = (int *)malloc((numVer + 1) * sizeof(int));
    dfs(graph, numVer, result);
    printf("The result from the topological sort is:\n");
    int i;
    for (i = numVer; i >= 1; i--)
    {
        printf("%d\t", result[i]);
    }
    free(sortedArray);
    free(result);
    return 0;
}
