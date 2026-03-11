#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 5
#define INF 99999

/* Sample Graph */
int graph[V][V] = {
    {0,4,1,0,0},
    {4,0,2,5,0},
    {1,2,0,8,10},
    {0,5,8,0,2},
    {0,0,10,2,0}
};

/* ---------- DIJKSTRA ---------- */

int minDist(int dist[], int visited[])
{
    int min = INT_MAX, index;

    for(int i=0;i<V;i++)
        if(!visited[i] && dist[i] <= min)
        {
            min = dist[i];
            index = i;
        }

    return index;
}

void dijkstra()
{
    clock_t start,end;
    start = clock();

    int dist[V], visited[V];

    for(int i=0;i<V;i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[0] = 0;

    for(int count=0; count<V-1; count++)
    {
        int u = minDist(dist,visited);
        visited[u] = 1;

        for(int v=0; v<V; v++)
            if(!visited[v] && graph[u][v] &&
               dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("\nShortest distances:\n");

    for(int i=0;i<V;i++)
        printf("0 -> %d = %d\n",i,dist[i]);

    end = clock();

    printf("\nExecution Time: %lf sec",
           (double)(end-start)/CLOCKS_PER_SEC);

    printf("\nTime Complexity: O(V^2)");
    printf("\nSpace Complexity: O(V)");
    printf("\nApprox Space Used: %lu bytes\n",
           sizeof(dist)+sizeof(visited));
}

/* ---------- BFS ---------- */

void bfs()
{
    clock_t start,end;
    start = clock();

    int visited[V]={0};
    int queue[V];
    int front=0,rear=0;

    visited[0]=1;
    queue[rear++]=0;

    printf("\nBFS Order: ");

    while(front<rear)
    {
        int node=queue[front++];
        printf("%d ",node);

        for(int i=0;i<V;i++)
        {
            if(graph[node][i] && !visited[i])
            {
                visited[i]=1;
                queue[rear++]=i;
            }
        }
    }

    end = clock();

    printf("\nExecution Time: %lf sec",
           (double)(end-start)/CLOCKS_PER_SEC);

    printf("\nTime Complexity: O(V+E)");
    printf("\nSpace Complexity: O(V)");
}

/* ---------- BELLMAN FORD ---------- */

void bellman()
{
    clock_t start,end;
    start = clock();

    int dist[V];

    for(int i=0;i<V;i++)
        dist[i]=INT_MAX;

    dist[0]=0;

    for(int k=0;k<V-1;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(graph[i][j] && dist[i]!=INT_MAX &&
                   dist[i]+graph[i][j]<dist[j])
                    dist[j]=dist[i]+graph[i][j];

    printf("\nDistances:\n");

    for(int i=0;i<V;i++)
        printf("0 -> %d = %d\n",i,dist[i]);

    end = clock();

    printf("\nExecution Time: %lf sec",
           (double)(end-start)/CLOCKS_PER_SEC);

    printf("\nTime Complexity: O(VE)");
    printf("\nSpace Complexity: O(V)");
}

/* ---------- FLOYD WARSHALL ---------- */

void floyd()
{
    clock_t start,end;
    start = clock();

    int dist[V][V];

    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            dist[i][j]=graph[i][j];

    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(dist[i][k]+dist[k][j] < dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];

    printf("\nAll Pair Shortest Paths:\n");

    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
            printf("%4d ",dist[i][j]);
        printf("\n");
    }

    end = clock();

    printf("\nExecution Time: %lf sec",
           (double)(end-start)/CLOCKS_PER_SEC);

    printf("\nTime Complexity: O(V^3)");
    printf("\nSpace Complexity: O(V^2)");
}

/* ---------- ASTAR (Simplified demo) ---------- */

void astar()
{
    printf("\nA* Algorithm demonstration");
    printf("\nUses heuristic + cost function");
    printf("\nTime Complexity: O(E)");
    printf("\nSpace Complexity: O(V)");
}

/* ---------- JOHNSON ---------- */

void johnson()
{
    printf("\nJohnson Algorithm demonstration");
    printf("\nUsed for all-pairs shortest paths");
    printf("\nTime Complexity: O(V^2 log V + VE)");
    printf("\nSpace Complexity: O(V^2)");
}

/* ---------- MENU ---------- */

int main()
{
    int choice;

    while(1)
    {
        printf("\n\n--- Shortest Path Algorithms ---\n");

        printf("1. Dijkstra\n");
        printf("2. Bellman Ford\n");
        printf("3. Floyd Warshall\n");
        printf("4. BFS\n");
        printf("5. A*\n");
        printf("6. Johnson\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: dijkstra(); break;
            case 2: bellman(); break;
            case 3: floyd(); break;
            case 4: bfs(); break;
            case 5: astar(); break;
            case 6: johnson(); break;
            case 7: return 0;
            default: printf("Invalid choice");
        }
    }
}