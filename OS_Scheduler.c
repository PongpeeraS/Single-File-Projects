#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSize=5;

struct Process {
   int pid, bt, at, pri;
};

void fcfs(struct Process *proc);
void npsjf(struct Process *proc);
void roundrb(struct Process *proc, int qt);

int main(int argc, char* argv[]){

    FILE *fp;
    printf("%s %s %s\n",argv[0],argv[1],argv[2]);
    if(argc != 3){
        //error
        fprintf(stderr,"usage: ./scheduler <input file> <scheduling algorithm>");
        return -1;
    }
    fp = fopen(argv[1],"r");//read the file
    fscanf(fp,"%d",&maxSize);//re calculates the maxsize
    struct Process test[maxSize];
    int i;
    for(i=0;i<maxSize;i++){
        fscanf(fp,"%d, %d, %d, %d",&test[i].pid,&test[i].bt,&test[i].at,&test[i].pri);
        printf("%d, %d, %d, %d\n",test[i].pid,test[i].bt,test[i].at,test[i].pri);
    }
    printf("\n");
    if(!strcmp(argv[2], "FCFS"))//if case for FCFS
    {
        printf("FCFS selected\n\n");
        fcfs(&test);
    }
    else if(!strcmp(argv[2], "SJF"))//if case for SJF
    {
        printf("SJF (non-preemptive) selected\n\n");
        npsjf(&test);
    }
    else //for quantum time
    {
        long convert = strtol(argv[2],NULL,10); // String to Long
	int  numz = (int)convert;
	printf("RR selected with q = %d\n\n", numz);
        roundrb(&test, numz);// Then cast long to int
    }
	exit(0);

}

void fcfs(struct Process *proc){
    int i, j,
        respT, waitT, turnT,
        currentT=0, tRespT=0, tWaitT=0, tTurnT=0; //Accumulators
    /*1. - 3. sorts the process according to the scheduling method & conditions given in the PDF file*/
    /*1. Sorting the order of processes by arrival time at, using bubble sort*/
    struct Process swap;
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if (proc[j].at > proc[j+1].at){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*2. Sorting the order of processes by priority pri, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].pri > proc[j+1].pri)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*3. Sorting the order of processes by burst time bt, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].pri == proc[j+1].pri) && (proc[j].bt > proc[j+1].bt)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*Calculation of time for each process*/
    for(i=0;i<maxSize;i++){
        respT = currentT - proc[i].at;
        waitT = currentT - proc[i].at;
        currentT += proc[i].bt;
        turnT = proc[i].bt + waitT;

        tRespT += respT;
        tWaitT += waitT;
        tTurnT += turnT;
        printf("%d, %d, %d, %d\n", proc[i].pid, respT, waitT, turnT);
    }
    /*Calculation of averages of all processes*/
    float tPut      = (float)maxSize/(float)currentT,  avgRespT = (float)tRespT/(float)maxSize,
          avgWaitT  = (float)tWaitT/(float)maxSize,    avgTurnT = (float)tTurnT/(float)maxSize;
    printf("%.2f,%.2f,%.2f,%.2f\n", tPut, avgRespT, avgWaitT, avgTurnT);
}

void npsjf(struct Process *proc){
    int i, j, k,
        respT, waitT, turnT,
        currentT=0, tRespT=0, tWaitT=0, tTurnT=0; //Accumulators
    struct Process swap;
    /*1. - 3. sorts the process according to the scheduling method & conditions given in the PDF file*/
    /*1. Sorting the order of processes by arrival time at, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if (proc[j].at > proc[j+1].at){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*2. Sorting the order of processes by burst time bt, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].bt > proc[j+1].bt)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*3. Sorting the order of processes by priority pri, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].bt == proc[j+1].bt) && (proc[j].pri > proc[j+1].pri)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*Calculation of time for each process*/
    for(i=0;i<maxSize;i++){
        respT = currentT - proc[i].at;
        waitT = currentT - proc[i].at;
        turnT = proc[i].bt + waitT;
        currentT += proc[i].bt;

        tRespT += respT;
        tWaitT += waitT;
        tTurnT += turnT;
        printf("%d, %d, %d, %d\n", proc[i].pid, respT, waitT, turnT);
        /*Sort the burst time bt of processes that have arrived & not complete*/
        for (j=i;j<(maxSize-1);j++){
            for (k=i+1;k<maxSize-j-1;k++){
                if (proc[k].bt > proc[k+1].bt){
                    swap = proc[k];
                    proc[k] = proc[k+1];
                    proc[k+1] = swap;
                }
            }
        }
    }
    /*Calculation of averages of all processes*/
    float tPut      = (float)maxSize/(float)currentT,  avgRespT = (float)tRespT/(float)maxSize,
          avgWaitT  = (float)tWaitT/(float)maxSize,    avgTurnT = (float)tTurnT/(float)maxSize;
    printf("%.2f,%.2f,%.2f,%.2f\n", tPut, avgRespT, avgWaitT, avgTurnT);
}
void roundrb(struct Process *proc, int qt){
    int remTime[maxSize]; //Remaining time
    struct Process swap;
    int i, j,
        waitT=0, respT=0, turnT=0,checker[maxSize],
        currentT=0, totalR=0, totalW=0, totalT=0,
        tRespT[maxSize], tWaitT[maxSize], tTurnT[maxSize], lastT[maxSize],
        counter = 0;
    /*1. Sorting the order of processes by arrival time at, using bubble sort*/
    for (i=0;i<maxSize-1;i++){
        for (j=0;j<maxSize-i-1;j++){
            if (proc[j].at > proc[j+1].at){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*2. Sorting the order of processes by priority pri, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].pri > proc[j+1].pri)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*3. Sorting the order of processes by burst time bt, using bubble sort*/
    for (i=0;i<(maxSize-1);i++){
        for (j=0;j<maxSize-i-1;j++){
            if ((proc[j].at == proc[j+1].at) && (proc[j].pri == proc[j+1].pri) && (proc[j].bt > proc[j+1].bt)){
                swap = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = swap;
            }
        }
    }
    /*Set the counter for remaining time of each process*/
    for(i=0;i<maxSize;i++){
        remTime[i] = proc[i].bt;
        tRespT[i] = 0;
        tWaitT[i] = 0;
        tTurnT[i] = 0;
        lastT[i] = proc[i].at;   //The time when the burst round ended
    }
    /*Calculation of time for each process*/
    while(1){
        for(i=0;i<maxSize;i++){
            if(remTime[i] > 0){

                respT = 0;
                waitT = currentT - lastT[i];

                    turnT = 88; // 88 is X
                printf("%d, %d, %d, %c\n", proc[i].pid, respT, waitT, turnT);

                if(remTime[i]-qt <= 0){
                    currentT += remTime[i];
                    remTime[i] = 0;
                    lastT[i] = currentT;
                    tTurnT[i] = currentT - proc[i].at;
                }
                else{
                    remTime[i] -= qt;
                    currentT += qt;
                    lastT[i] = currentT;
                }
                tRespT[i] += respT;
                tWaitT[i] += waitT;

                }
        }
        for(i=0;i<maxSize;i++){
            if(remTime[i] == 0) counter++;
        }
        if(counter == maxSize) break;
        else counter = 0;
    }
    printf("\n");
    for(i=0;i<maxSize;i++){
        printf("%d, %d, %d, %d\n", proc[i].pid, tRespT[i], tWaitT[i], tTurnT[i]);
        totalR += tRespT[i];
        totalW += tWaitT[i];
        totalT += tTurnT[i];
    }
    /*Calculation of averages of all processes*/
    float tPut      = (float)maxSize/(float)currentT,  avgRespT = (float)totalR/(float)maxSize,
          avgWaitT  = (float)totalW/(float)maxSize,    avgTurnT = (float)totalT/(float)maxSize;
    printf("%.2f,%.2f,%.2f,%.2f\n", tPut, avgRespT, avgWaitT, avgTurnT);
}



