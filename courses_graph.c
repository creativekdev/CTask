#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2

 
void DFS_visit(int u, int N, int graph[][1001], int *curN, int res[], int color[], int deg[]) {
    int v;
    color[u] = BLACK;    

    for (v = 0; v < N ; v++) {
        if (graph[u][v] == 1 && color[v] == WHITE) {
        	DFS_visit(v, N, graph, curN, res, color, deg);
        }
    }
    res[(*curN)] = u;
    (*curN)++;        
}

int main(){
    char fileName[31];
    char line[1001];
    char c;
    char courses[101][1001];
    char tmpcourses[1001];
    int deg[101];
    int N =0;
    int i, j, k;

    printf("This program will read, from a file, a list of courses and their prerequesites and will print the list in which to take courses.\n");
    printf("Enter file name: ");
    scanf("%s%c", fileName, &c);


    //open the file
    FILE *fp;
    fp = fopen(fileName, "r");
    while(fgets(courses[N], sizeof(courses[N]), fp) != NULL) N++;
    fclose(fp);

    //store only the courses as a string array
    printf("Number of vertices in built graph: N = %d\n", N);
    char className[101][31];
    int classNameCnt = 0;
	char * token;
  	int graph[101][1001];
  	for(i = 0; i < N ; i ++) 
  		for(j = 0;  j < N; j++)
  			graph[i][j] = 0;
  			
  	for(i = 0; i < N; i++) deg[i] = 0;
  	puts("Vertex - coursename correspondence");
    for(i=0; i<N; i++){
    	strcpy(tmpcourses, courses[i]);
    	token = strtok(tmpcourses, " \n");
    	if(strlen(token) == 0) continue;
    	for(j = 0; j < classNameCnt; j++) if(strcmp(token, className[j]) == 0) break;
    	if(j == classNameCnt) {
    		strcpy(className[classNameCnt], token);
	        classNameCnt++;
	        printf("%d - %s\n", classNameCnt, className[classNameCnt - 1]);
		}
      	token = strtok(NULL, " \n");
  }
    for(i=0; i<N; i++){
    	strcpy(tmpcourses, courses[i]);
    	token = strtok(tmpcourses, " \n");
    	if(strlen(token) == 0) continue;
    	for(j = 0; j < classNameCnt; j++) if(strcmp(token, className[j]) == 0) break;
      	token = strtok(NULL, " \n");
    	
    	while( token != NULL ) {
	    	if(strlen(token) > 0){
		    	for(k = 0; k < classNameCnt; k++) if(strcmp(token, className[k]) == 0) break;
				graph[k][j] = 1;
				deg[j]++;	    		
			}
	      	token = strtok(NULL, " \n");
   		}
    }
    
    printf("Adjacency Matrix:\n");
    printf("   |");
    for(i = 0; i < N; i++) {
    	printf("   %d", i);
	}
	printf("\n");
	
	for(i = 0; i < N + 1; i++) printf("----");
	puts("");
    for (i = 0; i < N; i++) {
    	printf("  %d|", i);
        for (j = 0; j < N; j++) {
            printf("   %d", graph[i][j]);
        }
        printf("\n");
    }
 	
 	int color[101];
    for (i = 0; i < N; i++) {
        color[i] = WHITE;
        
    }
    int curN = 0;
    int res[101];
    for (i = 0; i < N; i++) {
        if (color[i] == WHITE) {
            DFS_visit(i, N, graph, &curN, res, color, deg);
        }
    }
    int flag = 0;
	int pos[101];
	for(i = N - 1; i >=0; i--) {
		pos[res[i]] =  N - 1 - i;
	}
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			if(graph[i][j] == 1 && pos[i] > pos[j]) {
				flag = 1;
			}
		}
	}
    if(flag) {
    	printf("There was at least one cycle. There is no possible ordering of the courses.\n");
	}
	else{
		puts("Order in which to take courses:");
		for(i = N - 1; i >= 0; i --) {
			printf("%d. - %s (corresponds to graph vertex %d)\n", N - i, className[res[i]], res[i] );
		}
	}
 
    return 0;
}
