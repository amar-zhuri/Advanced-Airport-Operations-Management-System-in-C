#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct airport{
    char name[31];
    char city[31];
    int runways;
    int time;
}AIRPORT;

int cmp(const void *a, const void *b){
    AIRPORT *left = (AIRPORT *)a;
    AIRPORT *right = (AIRPORT *)b;

    if(left->runways != right->runways){  
        return -(left->runways-right->runways);

    }

    if(left->time != right ->time){
       return -(left->time-right->time);
    }

   return strcmp(left->name, right->name);
}

int query(AIRPORT *airports,int length){
    int max = airports[0].runways;

    for(int i = 1 ; i < length ;i++){
        if(airports[i].runways > max){
            max = airports[i].runways;
        }
    }
    return max;
}



int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "No first argument\n");
        return 1;
    }

    FILE *fin = fopen(argv[1],"r");

    if(!fin){
        fprintf(stderr, "File does not exist\n");
        return 2;
    }

    char line[102];
    AIRPORT airports[20];
    int length=0;

    while(fgets(line,102,fin)){
     line[strlen(line) - 1] = '\0';

     char *name = strtok(line, ";");
     char *city = strtok(NULL, ";");
     char *runways = strtok(NULL,";");
     char *time = strtok(NULL, ";");

     strcpy(airports[length].name,name);
     strcpy(airports[length].city,city);
     airports[length].runways = atoi(runways);
     airports[length].time = atoi(time);

     length++;
    }

    fclose(fin);

        if(argc < 3){
        fprintf(stderr,"Second Argument Missing\n");
        return 3;
    }

 FILE *fout = fopen(argv[2], "w");

 if(!fout){
    fprintf(stderr, "2nd File Cant open");
    return 4;
 }

    qsort(airports, length, sizeof(AIRPORT),cmp);


    for(int i = 0 ; i < length;  i++){
        fprintf(fout, "%s;%s;%d;%d\n",
        airports[i].name,
        airports[i].city,
        airports[i].runways,
        airports[i].time);

    }
    fclose(fout);
    printf("%d\n", query(airports, length));

    return EXIT_SUCCESS;
}