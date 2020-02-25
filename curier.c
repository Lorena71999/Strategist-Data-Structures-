#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INFINIT 9999

typedef struct Graf_Metrou{
    int N,M;
    int **matrice_de_adiacenta_distanta;
}graf_metrou;

typedef struct Client{
    int timp_fata_de_statia_de_metrou;
    char *nume_client;
    int suma_de_platit;
}clienti;

typedef struct strazi_intre_clienti
{

    char* nume_client1;
    char* nume_client2;
    int timp;
}strazi;


typedef struct Statie_Metrou{
    char *nume;
    int Comenzi_livrare_client;
    int numar_clienti; 
    clienti* cl;
    strazi* strazi_intre_clienti;
}statie_metrou;



typedef struct Graf_Client{
    int numarclienti, strazi_intre_clienti2;
    int **matrice_de_adiacenta_timp;
}graf_client;


typedef struct rute_metrou
{
    char* nume_statie1;
    char* nume_statie2;
    int distanta;
}rute_metrou;

typedef struct Point{
  int i;
  int j;
}Point;

int **matrice_de_parcurgere_strazi_pana_la_sediu;
int numar_strazi_matrice;
int dimensiune_drum_total = 0 ;
int  *drumuri;
int aux_dim_drum_total = 0;

graf_client * create_graf_client (int numar_clienti, strazi* strazi_intre_clienti,clienti* client, int numar_strazi_intre_clienti, int st){
    int i, j, k, o=0;
    graf_client * g[st];
    g[st] = (graf_client*)malloc(sizeof(graf_client));
    g[st]->numarclienti = numar_clienti;
    if (g == NULL) {
        printf ( " no memory for this graph");
        return NULL;
    }
    g[st]->matrice_de_adiacenta_timp = (int **)malloc(g[st]->numarclienti * sizeof(int*));
    for (i = 0; i < g[st]->numarclienti; i++)
        g[st]->matrice_de_adiacenta_timp[i] = (int *) calloc(g[st]->numarclienti, sizeof(int));
    if (g[st]->matrice_de_adiacenta_timp == NULL) {
        printf ( "no memory for this matrix");
        return NULL;
    }
    j = 0;
    k = o = 0;
    g[st]->strazi_intre_clienti2 = 0;
    for(i = 0; i < numar_strazi_intre_clienti; i++){
        for(j = 0; j < numar_clienti; j++){
            if(strcmp(strazi_intre_clienti[i].nume_client1, client[j].nume_client) == 0){
                k = j;
            }
            if(strcmp(strazi_intre_clienti[i].nume_client2, client[j].nume_client) == 0){
                o = j;
            }
        }
        
        g[st]->matrice_de_adiacenta_timp[k][o] = strazi_intre_clienti[i].timp;
        g[st]->matrice_de_adiacenta_timp[o][k] = strazi_intre_clienti[i].timp;
         
    }   
    return g[st];
}

graf_metrou * create (int numar_statii, statie_metrou* statii, rute_metrou* rute, int numar_rute){
    int i, j, k, o;
   graf_metrou *g_metrou = (graf_metrou*) malloc (sizeof(graf_metrou));
    g_metrou->N = numar_statii;
    if (g_metrou == NULL) {
        printf ( " no memory for this graph");
        return NULL;
    }
    g_metrou->matrice_de_adiacenta_distanta = (int **)malloc(g_metrou->N*sizeof(int*));
    for (i = 0; i < g_metrou->N; i++)
        g_metrou->matrice_de_adiacenta_distanta[i] = (int *) calloc(g_metrou->N, sizeof(int));
    if (g_metrou->matrice_de_adiacenta_distanta == NULL) {
        printf ( "no memory for this matrix");
        return NULL;
    }
    g_metrou->M = 0;
    for(i=0;i < numar_rute; i++){
        for(j=0; j < numar_statii; j++){
            if(strcmp(rute[i].nume_statie1, statii[j].nume) == 0)
                k = j;
            if(strcmp(rute[i].nume_statie2, statii[j].nume) == 0)
                o = j;
        }
        g_metrou->matrice_de_adiacenta_distanta[k][o] = rute[i].distanta;
        g_metrou->matrice_de_adiacenta_distanta[o][k] = rute[i].distanta;
    }

    return g_metrou;
}

void legatura(int numar_statii, statie_metrou* statie, char* x, graf_metrou *g_metrou, FILE* f2){
    int i, j, poz;
    for(i = 0;i < numar_statii; i++){
        if(strcmp(x, statie[i].nume) == 0){
            poz = i;
        }
    }
    for (j = 0; j < g_metrou->N; j++){
            if(g_metrou->matrice_de_adiacenta_distanta[poz][j] != 0 && g_metrou->matrice_de_adiacenta_distanta[poz][j] != INFINIT )
                fprintf(f2, "%s ",statie[j].nume);
        }
}

graf_metrou* adauga_ruta(int numar_statii, statie_metrou* statii, char* x, char* y, int distanta, graf_metrou* g_metrou, FILE* f2){
    int i, poz1, poz2;
    for(i=0;i<numar_statii;i++)
    {
        if(strcmp(x, statii[i].nume) == 0){
            poz1=i;
        }
        if(strcmp(y, statii[i].nume) == 0){
            poz2 = i;
        }
    }
    g_metrou->matrice_de_adiacenta_distanta[poz1][poz2] = distanta;
    g_metrou->matrice_de_adiacenta_distanta[poz2][poz1] = distanta;
    return g_metrou;

}

graf_metrou* sterge_ruta(int numar_statii, statie_metrou* statii,char* x,char* y, graf_metrou* g_metrou, FILE* f2){
    int i, poz1, poz2;
    for(i = 0; i < numar_statii; i++)
    {
        if(strcmp(x, statii[i].nume) == 0){
            poz1 = i;
        }
        if(strcmp(y, statii[i].nume) == 0){
            poz2 = i;
        }
    }
    g_metrou->matrice_de_adiacenta_distanta[poz1][poz2] = 0;
    g_metrou->matrice_de_adiacenta_distanta[poz2][poz1] = 0;
    return g_metrou;

}

void comanda_statie(int numar_statii, statie_metrou* statii, int valoare_suma, FILE * f2){

    int i, k = 0, j;    
    int * suma_bani_totala;
    char ** statii_bune  = (char**)malloc(sizeof(char*)*numar_statii);
    suma_bani_totala = (int*)calloc(numar_statii, sizeof(int));
    for(i = 0; i < numar_statii; i ++)
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            suma_bani_totala[i] =suma_bani_totala[i] + statii[i].cl[j].suma_de_platit;
        }
    for(i = 0; i < numar_statii; i++)
    {
        if(suma_bani_totala[i] >= valoare_suma){
            statii_bune[k] = (char*)malloc(sizeof(char*)*numar_statii);
            strcpy(statii_bune[k],statii[i].nume);
            k++;
        }
    }
    for(i = 0; i < k; i++){
        fprintf(f2, "%s ", statii_bune[i]);
    }
    for( i = 0; i < k; i++){
        char* aux = statii_bune[i];
        free(aux);
    }
    free(suma_bani_totala);
}

void drum_strada(int G[][100],int n,int startnode, char* client1, char* client2, int numar_statii, statie_metrou* statii, FILE* f2)
{
 
    int visited[n],count,mindistance,nextnode,i,j, pozi;
    int cost[n][n],distance[n],pred[n], l=0, pozitie1, pozitie2, a[50];
    for(i=0;i<numar_statii;i++){
        for(j=0;j<statii[i].numar_clienti;j++){
            if(strcmp(client1,statii[i].cl[j].nume_client)==0){
                pozitie1=j;
                pozi=i;
            }
            if(strcmp(client2,statii[i].cl[j].nume_client)==0){
                pozi = i;
                pozitie2=j;
            }
        }
    }
    startnode=pozitie1;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINIT;
            else
                cost[i][j]=G[i][j];
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINIT;
        for(i=0;i<n;i++){
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }      
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }
    for(i=0;i<n;i++)
        if(i==pozitie2)
        {

            j=i;
            do
            {
                j=pred[j];
                a[l]=j;
                l++;
            }while(j!=startnode);
    }
    for(i=l-1;i>=0;i--){
        fprintf(f2, "%s ",statii[pozi].cl[a[i]].nume_client);
   
    }
    fprintf(f2, "%s ",statii[pozi].cl[pozitie2].nume_client);
    fprintf(f2, "\n");

}

void conexiune(int numar_statii, statie_metrou* statii, char* x, char* y, graf_client* g_clienti, FILE *f2)
{
    int i, j, poz1, poz2;

    for(i = 0; i < numar_statii; i++)
    {
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            if(strcmp(statii[i].cl[j].nume_client, x) == 0){
                poz1 = j;

            }
            if(strcmp(statii[i].cl[j].nume_client, y) == 0)
                poz2 = j;

        }
    }

    if(g_clienti->matrice_de_adiacenta_timp[poz1][poz2] != 0)
        fprintf(f2, "OK");
    else fprintf(f2, "NO");
    fprintf(f2, "\n" );
}

void drum_metrou(int G[][100],int n,int startnode, char* statie1, char* statie2, int numar_statii, statie_metrou * statii, FILE* f2)
{
    int visited[n], count, mindistance, nextnode, i, j;
    int cost[n][n], distance[n], pred[n], l=0, pozitie1, pozitie2, a[50];
    for(i = 0; i < numar_statii; i++){
            if(strcmp(statie1, statii[i].nume) == 0){
                pozitie1 = i;
            }
            if(strcmp(statie2, statii[i].nume) == 0){
                pozitie2 = i;
            }
        }
    startnode = pozitie1;
    for(i = 0;i < n; i++)
        for(j = 0; j < n; j++)
            if(G[i][j] == 0)
                cost[i][j] = INFINIT;
            else
                cost[i][j] = G[i][j];
    for(i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    
    while(count < n - 1)
    {
        mindistance = INFINIT;
        for(i = 0; i < n; i++){
            if(distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        }
            visited[nextnode] = 1;
            for(i = 0; i < n; i++)
                if(!visited[i])
                    if(mindistance + cost[nextnode][i] < distance[i])
                    {
                        distance[i] = mindistance+cost[nextnode][i];
                        pred[i] = nextnode;
                    }
        count++;
    }
    for(i = 0;i < n; i++)
        if(i==pozitie2)
        {
            j=i;
            do
            {
                j=pred[j];
                a[l]=j;
                l++;
            }while(j!=startnode);
    }
    for(i=l-1;i>=0;i--)
        fprintf(f2, "%s ",statii[a[i]].nume);
    fprintf(f2, "%s ", statii[pozitie2].nume );
    fprintf(f2, "\n");

}

graf_metrou* blocaj_tunel(int numar_statii, statie_metrou* statii, char* x, char *y, graf_metrou *g_metrou, FILE *f2)
{
    int i, poz1, poz2;
    for(i = 0; i < numar_statii; i++)
    {
        if(strcmp(x, statii[i].nume) == 0)
            poz1 = i;
        if(strcmp(y, statii[i].nume) == 0)
            poz2 = i;
    }

    g_metrou->matrice_de_adiacenta_distanta[poz1][poz2] = INFINIT;
    g_metrou->matrice_de_adiacenta_distanta[poz2][poz1] = INFINIT;

    return g_metrou;
}

graf_client* blocaj_strada(int numar_statii, statie_metrou* statii, char* x, char* y, graf_client* g_clienti, FILE *f2)
{
    int i, j, poz1, poz2;
    for(i = 0; i < numar_statii; i++)
    {
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            if(strcmp(statii[i].cl[j].nume_client, x) == 0)
                poz1 = j;
            if(strcmp(statii[i].cl[j].nume_client, y) == 0)
                poz2 = j;
        }
    }

    if(g_clienti->matrice_de_adiacenta_timp[poz1][poz2] != 0)
    {
        g_clienti->matrice_de_adiacenta_timp[poz1][poz2] = INFINIT;
        g_clienti->matrice_de_adiacenta_timp[poz2][poz1] = INFINIT;
    }

    return g_clienti;
}

graf_client* adauga_strada(int numar_statii, statie_metrou* statii, char* x, char* y, int distanta, graf_client* g_clienti, FILE *f2)
{
    int i, j, poz1, poz2;

    for(i = 0; i < numar_statii; i++)
    {
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            if(strcmp(statii[i].cl[j].nume_client, x) == 0){
                poz1 = j;

            }
            if(strcmp(statii[i].cl[j].nume_client, y) == 0)
                poz2 = j;

        }
    }
        
        g_clienti->matrice_de_adiacenta_timp[poz1][poz2] = distanta;
        g_clienti->matrice_de_adiacenta_timp[poz2][poz1] = distanta;

    return g_clienti;
}

graf_client* sterge_strada(int numar_statii, statie_metrou* statii, char* x, char* y, graf_client* g_clienti, FILE *f2)
{
    int i, j, poz1, poz2;

    for(i = 0; i < numar_statii; i++)
    {
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            if(strcmp(statii[i].cl[j].nume_client, x) == 0){
                poz1 = j;
            }
            if(strcmp(statii[i].cl[j].nume_client, y) == 0){
                poz2 = j;
            }
        }
    }
        
        g_clienti->matrice_de_adiacenta_timp[poz1][poz2]=0;
        g_clienti->matrice_de_adiacenta_timp[poz2][poz1]=0;

    return g_clienti;
}
void timp_minim(statie_metrou* statii,FILE* f2, graf_client * g, int pozitia)
{
    int i,j,l, cel_mai_apropiat_client, st, timpul_minim, pozitie, numar_legaturi = 0, minim=100;
    int *vec;
    vec = ( int*) malloc( sizeof(int)*numar_legaturi);
    int **graf_client = (int**)malloc(sizeof(int*)*statii[pozitia].numar_clienti);
    for(i = 0; i < statii[pozitia].numar_clienti; i++ )
    	graf_client[i] = (int*)malloc(sizeof(int)*statii[pozitia].numar_clienti+1);
    cel_mai_apropiat_client = 100;


    for(i = 0; i < statii[pozitia].numar_clienti; i++ )
    {
        if(cel_mai_apropiat_client>statii[pozitia].cl[i].timp_fata_de_statia_de_metrou)
            {

                cel_mai_apropiat_client=statii[pozitia].cl[i].timp_fata_de_statia_de_metrou;
                st=i;
            }
        }

    for(i = 0; i < statii[pozitia].numar_clienti; i++)
        for(j = 0; j < statii[pozitia].numar_clienti; j++)
            graf_client[i][j] = g->matrice_de_adiacenta_timp[i][j];

    timpul_minim = cel_mai_apropiat_client;

    for(j = 0; j < statii[pozitia].numar_clienti; j++)
    {
        for(i= 0; i < statii[pozitia].numar_clienti ; i++){
            if(g->matrice_de_adiacenta_timp[st][i] !=0 ){
                vec[numar_legaturi] = g->matrice_de_adiacenta_timp[st][i];
                numar_legaturi++;   
                    }
            }
            for(i = 0; i < numar_legaturi; i++){
                if(minim > vec[i])
                    minim = vec[i];
            }

            for(i = 0; i < statii[pozitia].numar_clienti; i++)
                if(minim == g->matrice_de_adiacenta_timp[st][i])
                    pozitie=i;
            numar_legaturi=0;
            minim = 100;
            timpul_minim +=  g->matrice_de_adiacenta_timp[st][pozitie];

            for(l = 0; l < statii[pozitia].numar_clienti; l++)
                {
                    g->matrice_de_adiacenta_timp[st][l] = 0;
                    g->matrice_de_adiacenta_timp[l][st] = 0;
                }
            st=pozitie;
        }

    for(i = 0; i < statii[pozitia].numar_clienti; i++)
        for(j = 0; j < statii[pozitia].numar_clienti; j++)
             g->matrice_de_adiacenta_timp[i][j] = graf_client[i][j]; 

    timpul_minim +=  statii[pozitia].cl[st].timp_fata_de_statia_de_metrou;

    fprintf(f2,"%d\n",timpul_minim);
    free(vec);
}
void printArray(Point* arr, int n)
{
  for(int i = 0; i < n; i++)
  {
    aux_dim_drum_total += matrice_de_parcurgere_strazi_pana_la_sediu[arr[i].i][arr[i].j];
    drumuri[dimensiune_drum_total] = aux_dim_drum_total;

  }
    aux_dim_drum_total = 0;
    dimensiune_drum_total++;

}

int printPaths(int n, int m, Point *arr, int N, int curCell)
{
  arr[curCell].i = n;
  arr[curCell].j = m;
  
  if(n == 0 && m == 0)
  {
    printArray(arr, N);
    return 0;
  }
  
  if(n == 0)
  {
    printPaths(n, m-1, arr, N, curCell-1);
    return 1;
  }
  if(m == 0)
  {
    printPaths(n-1, m, arr, N, curCell-1);
    return 1;
  }
  return printPaths(n, m-1, arr, N, curCell-1) + printPaths(n-1, m, arr, N, curCell-1);
}
void back(int numar_strazi_matrice, FILE* f1, FILE* f2)
{
    int aux, i, j;
	matrice_de_parcurgere_strazi_pana_la_sediu = (int**)malloc(sizeof(int*)*numar_strazi_matrice);
    for(i = 0; i < numar_strazi_matrice; i++){
        matrice_de_parcurgere_strazi_pana_la_sediu[i] = (int*)malloc(sizeof(int));
        for(j = 0; j < numar_strazi_matrice; j++)
        {
            fscanf(f1, "%d", &aux);
            matrice_de_parcurgere_strazi_pana_la_sediu[i][j] = aux;
        }
    }

    Point arr[2 * (numar_strazi_matrice) - 1];
    drumuri = (int*)malloc(sizeof(int)*100);
    printPaths((numar_strazi_matrice) - 1, (numar_strazi_matrice) - 1, arr, 2 * (numar_strazi_matrice) - 1, 2 * (numar_strazi_matrice) - 2);

    int min = drumuri[0];
    for(i = 1; i < dimensiune_drum_total; i++)
        if(drumuri[i] < min)
        {
            min = drumuri[i];
        }
    fprintf(f2, "%d\n", min);
}
int main(int argc, char *argv [])
{
    FILE *f1;
    FILE *f2;
    f1 = fopen(argv[1],"rt");
    if(f1==NULL){
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    char * operatie;
    char ** vec_cerinte;
    char * x, *y;
    int distanta, valoare_suma, pozitie, pozi, l, G[100][100], numar_statii,  numar_rute, numar_operatii_strategie, i, j, k = 0, w=0;
    fscanf(f1, "%d", &numar_statii);
    operatie = (char*)malloc(sizeof(char)*20);
    statie_metrou* statii;
    statii = (statie_metrou*)malloc(sizeof(statie_metrou) * (numar_statii));
    rute_metrou* rute;
    int* numar_strazi_intre_clienti;
    numar_strazi_intre_clienti = (int*)malloc(sizeof(int)*30);

    graf_client **g = (graf_client**)malloc(sizeof(graf_client*)*numar_statii);
    for(i = 0; i < numar_statii; i ++)
    {

        statii[i].nume = (char*)malloc(sizeof(char)*30);
        fscanf(f1, "%s", statii[i].nume);
        fscanf(f1, "%d", &statii[i].numar_clienti);
        statii[i].cl = (clienti*)malloc(sizeof(clienti)*statii[i].numar_clienti);
        for(k =0; k <  statii[i].numar_clienti; k++)
        {
            statii[i].cl[k].nume_client = (char*)malloc(sizeof(char)*30);
            fscanf(f1, "%s", statii[i].cl[k].nume_client);
            fscanf(f1, "%d", &statii[i].cl[k].timp_fata_de_statia_de_metrou);
            fscanf(f1, "%d", &statii[i].cl[k].suma_de_platit);
        }
        fscanf(f1, "%d", &numar_strazi_intre_clienti[i]);
        statii[i].strazi_intre_clienti = (strazi*)malloc(sizeof(strazi)*(numar_strazi_intre_clienti[i]));
        for(k = 0; k < numar_strazi_intre_clienti[i]; k++)
        {
            statii[i].strazi_intre_clienti[k].nume_client1 = (char*)malloc(sizeof(char)*30);
            statii[i].strazi_intre_clienti[k].nume_client2 = (char*)malloc(sizeof(char)*30);
            fscanf(f1, "%s", statii[i].strazi_intre_clienti[k].nume_client1);
            fscanf(f1, "%s", statii[i].strazi_intre_clienti[k].nume_client2);
            fscanf(f1, "%d", &statii[i].strazi_intre_clienti[k].timp);


        }
        g[i] = create_graf_client(statii[i].numar_clienti,statii[i].strazi_intre_clienti, statii[i].cl, numar_strazi_intre_clienti[i], i);
    }
    fscanf(f1, "%d", &numar_rute);
    rute = (rute_metrou*)malloc(sizeof(rute_metrou)*numar_rute);
    for(i = 0; i < numar_rute; i++)
    {
        rute[i].nume_statie1 = (char*)malloc(sizeof(char)*20);
        rute[i].nume_statie2 = (char*)malloc(sizeof(char)*20);
        fscanf(f1, "%s", rute[i].nume_statie1);
        fscanf(f1, "%s", rute[i].nume_statie2);
        fscanf(f1, "%d", &rute[i].distanta);
    }   
    fscanf(f1, "%d", &numar_operatii_strategie);
    graf_metrou *g_metrou;
    g_metrou = create(numar_statii, statii, rute, numar_rute);

    f2 = fopen(argv[2],"w");
    if(f2==NULL){
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    vec_cerinte = (char**)malloc(sizeof(char*)*numar_operatii_strategie);
    x = (char*)malloc(sizeof(char)*20);
    y = (char*)malloc(sizeof(char)*20);
    for(i = 0; i < numar_operatii_strategie; i++)
    {
        vec_cerinte[i] = (char*)malloc(sizeof(char)*30);
        fscanf(f1,"%s",vec_cerinte[i]);
        if(strcmp(vec_cerinte[i], "legatura") == 0){
            fscanf(f1,"%s", x);
            legatura(numar_statii, statii, x, g_metrou, f2);
            fprintf(f2, "\n"); 
        }
        if(strcmp(vec_cerinte[i], "adauga_ruta") == 0){
            fscanf(f1,"%s", x);
            fscanf(f1,"%s", y);
            fscanf(f1,"%d", &distanta);
            g_metrou = adauga_ruta(numar_statii, statii, x, y, distanta, g_metrou, f2);

        }
        if(strcmp(vec_cerinte[i], "comanda_statie") == 0){
            fscanf(f1, "%d", &valoare_suma);
            comanda_statie(numar_statii, statii, valoare_suma, f2);
            fprintf(f2, "\n");
        }
        if(strcmp(vec_cerinte[i], "sterge_ruta") == 0){
            fscanf(f1,"%s", x);
            fscanf(f1,"%s", y);
            g_metrou = sterge_ruta(numar_statii, statii, x, y, g_metrou, f2);

        }       
        if(strcmp(vec_cerinte[i], "drum_metrou") == 0){
            fscanf(f1,"%s", x);
            fscanf(f1,"%s", y);
            for(k = 0; k < g_metrou->N; k ++)
                for(j = 0; j <g_metrou->N; j++)
                    G[k][j] =g_metrou->matrice_de_adiacenta_distanta[k][j];
            drum_metrou(G,g_metrou->N,0,x,y,numar_statii,statii,f2);
        }
            if(strcmp(vec_cerinte[i], "drum_strada") == 0){
                fscanf(f1,"%s", x);
                fscanf(f1,"%s", y);
                for(k=0;k<numar_statii;k++){
                    for(j=0;j<statii[k].numar_clienti;j++){
                        if(strcmp(x,statii[k].cl[j].nume_client) == 0){
                            pozi=k;
                    }
                    if(strcmp(y,statii[k].cl[j].nume_client) == 0){
                        pozi = k;
                    }
                }
            }
            for(k = 0; k < g[pozi]->numarclienti; k++){
                for(j = 0; j < g[pozi]->numarclienti; j++){
                    G[k][j] = g[pozi]->matrice_de_adiacenta_timp[k][j];
                }
            }
            drum_strada(G,g[pozi]->numarclienti,0,x,y,numar_statii,statii,f2);
        }
        if(strcmp(vec_cerinte[i], "blocaj_tunel") == 0){
            fscanf(f1,"%s", x);
            fscanf(f1,"%s", y);
            blocaj_tunel(numar_statii, statii, x, y, g_metrou, f2);
        }
        if(strcmp(vec_cerinte[i], "sterge_strada") == 0){
            fscanf(f1,"%s", x);
            fscanf(f1,"%s", y);
            for(k = 0; k < numar_statii; k++)
                for(j = 0; j < statii[k].numar_clienti; j++)
                {
                                             
                    if(strcmp(x, statii[k].cl[j].nume_client) == 0){
                         pozitie = k;

                    }
                }
            g[pozitie] = sterge_strada(numar_statii, statii, x, y, g[pozitie], f2);
        }
        if(strcmp(vec_cerinte[i], "adauga_strada") == 0)
        {
            fscanf(f1, "%s", x);
            fscanf(f1, "%s", y);
            fscanf(f1, "%d", &distanta);
            for(k = 0; k < numar_statii; k++){
                for(j = 0; j < statii[k].numar_clienti; j++)
                {
                                    if(strcmp(x, statii[k].cl[j].nume_client) == 0){
                                    pozitie = k;
                                 }
                }
            }
                g[pozitie] = adauga_strada(numar_statii, statii, x, y, distanta, g[pozitie], f2);   
            for(k = 0; k < statii[pozitie].numar_clienti; k++){
                for(j = 0; j < statii[pozitie].numar_clienti; j++)
                    printf("%d",g[pozitie]->matrice_de_adiacenta_timp[k][j]);
                printf("\n" );   
            }
        }   
        if(strcmp(vec_cerinte[i], "blocaj_strada") == 0)
        {
            fscanf(f1, "%s", x);
            fscanf(f1, "%s", y);
            for(k = 0; k < numar_statii; k++)
                for(j = 0; j <statii[k].numar_clienti; j++)
                {
                    if(strcmp(x, statii[k].cl[j].nume_client) == 0)
                         pozitie = k;
                }
           blocaj_strada(numar_statii, statii, x, y, g[pozitie], f2);
        }
            if(strcmp(vec_cerinte[i], "conexiune") == 0){
                fscanf(f1,"%s", x);
                fscanf(f1,"%s", y);
                for(k = 0; k < numar_statii; k++){
                    for(j = 0; j < statii[k].numar_clienti; j++){
                    if(strcmp(x, statii[k].cl[j].nume_client) == 0){
                        pozi = k;
                    }
                    if(strcmp(y, statii[k].cl[j].nume_client) == 0){
                        pozi = k;
                    }
                }
            }
                conexiune(numar_statii, statii, x , y, g[pozi], f2);
            }   
        if(strcmp(vec_cerinte[i],"timp_statie") == 0)
        {
            fscanf(f1,"%s", x) ;
            for (l = 0; l < numar_statii; l++){
            if(strcmp(statii[l].nume, x) == 0)
                pozitie = l;
            }
            for(k = 0; k < g[pozitie]->numarclienti; k ++){
                for(j = 0; j <g[pozitie]->numarclienti; j++){
                    G[k][j] =g[pozitie]->matrice_de_adiacenta_timp[k][j];
                }
            }
           timp_minim(statii,f2,g[pozitie], pozitie);
        }
    }
    if(fscanf(f1, "%d", &numar_strazi_matrice) == EOF)
        w = 1;
    if(w == 0){
    	back(numar_strazi_matrice,f1,f2);
    }
    fclose(f1);
    fclose(f2);
    for(i = 0; i < numar_statii; i++)
    {
        int *aux = g_metrou->matrice_de_adiacenta_distanta[i];
        free(aux);
    }

    for(i = 0; i < numar_statii; i++)
        for(j = 0; j < statii[i].numar_clienti; j++)
        {
            int *aux = g[i]->matrice_de_adiacenta_timp[j];
            free(aux);
        }

    for(i = 0; i < numar_operatii_strategie; i++)
    {
        char *aux = vec_cerinte[i];
        free(aux);
    }
    free(statii->cl->nume_client);
    free(statii->strazi_intre_clienti->nume_client1);
    free(statii->strazi_intre_clienti->nume_client2);
    free(statii->cl);
    free(statii->strazi_intre_clienti);
    free(statii->nume);
    free(statii);
    free(rute->nume_statie1);
    free(rute->nume_statie2);
    free(rute);
    free(operatie);
    free(numar_strazi_intre_clienti);
    free(x);
    free(y);
    return 0;
}