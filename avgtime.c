#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct proc
{
	int pid;
	int bt;
	int at;
	int tat;
	int wt;
	int pri;
}
process[10];
struct proc temp;

int n;
int swt;

float awt;
int FCFS();
int Priority();
int Round_robin();
int SJFS();

int FCFS()
{
	FILE *fp;
	int b;
	char a;
	int i = 0;
	int j = 0;
	int flag1 = 0, flag2 = 1;
	if ((fp = fopen("FCFS.txt","r")) == NULL){
		printf("Error opening file\n");
	}
	
	
	while ((a = fgetc(fp)) != '#'){
		continue;
	}
	while (fscanf(fp,"%d",&b) != EOF){
		j++;
		if (flag1 == 0){
			process[i].pid = b;
			flag1 = 1;
			flag2 = 0;
		}
		else if (flag2 == 0){
			process[i].bt = b;
			flag2 = 1;
			flag1 = 0;
			i++;
		}
	}
	fclose(fp);
	printf("FCFS\n");
	n = (j/2);
	printf("Pid   Bursttime\n");
	for (i = 0;i < n; i++){
                  printf("%d\t%d\n", process[i].pid, process[i].bt);
          }

	process[0].wt = 0;
	for (i = 1; i < n; i++){
		process[i].wt = process[i-1].wt + process[i-1].bt;
	}
	for (i = 0;i < n; i++){
		printf("The waiting time of process %d is %d\n", i, process[i].wt);
	}
	for (i = 0; i < n; i++){
		swt = swt + process[i].wt;
	}
	awt = (float)swt/n;
	printf("The average waiting time is %f\n", awt);
	return 0;
}

int Priority()
{
	FILE *fp;
        int b;
        char a;
	int j = 0;
	int i = 0;
	int k = 0;
	awt = 0.0;
	swt = 0; 
        int flag1 = 0, flag2 = 1, flag3 = 1;
        if ((fp = fopen("Priority.txt","r")) == NULL){
                printf("Error opening file\n");
        }   
    
    
        while ((a = fgetc(fp)) != '#'){
                continue;
        }   
	while (fscanf(fp,"%d",&b) != EOF){
                j++;
                if (flag1 == 0){
                        process[i].pid = b;
                        flag1 = 1;
                        flag2 = 0;
                }
                else if (flag2 == 0){
                        process[i].bt = b;
                        flag2 = 1;
			flag3 = 0;
		}
		else if (flag3 == 0){
			process[i].pri = b;
			flag3 = 1;
			flag1 = 0;
			i++;
		}
	}
	fclose(fp);
	n = (j/3);
	printf("Priority\n");
        printf("Pid   Bursttime  Priority\n");
        for (i = 0; i < n; i++){
                  printf("%d\t%d\t   %d\n", process[i].pid, process[i].bt, process[i].pri);
        }
	for (i = 0; i < n; i++){
		for (k = i + 1; k < n; k++){
			if (process[i].pri > process[k].pri){
				temp = process[i];
				process[i] = process[k];
				process[k] = temp;
			}
		}
	}
	printf("Sorted process according to priority:\n");
	printf("Pid   Bursttime  Priority\n");
        for (i = 0; i < n; i++){
                  printf("%d\t%d\t   %d\n", process[i].pid, process[i].bt, process[i].pri);
        }
	process[0].wt = 0;
        for (i = 1; i < n; i++){
                process[i].wt = process[i-1].wt + process[i-1].bt;
        }
        for (i = 0;i < n; i++){
                printf("The waiting time of process %d is %d\n", i, process[i].wt);
        }
        for (i = 0; i < n; i++){
                swt = swt + process[i].wt;
        }
        awt = (float)swt/n;
        printf("The average waiting time is %f\n", awt);

	return 0;
}
int Round_robin()
{
	FILE *fp;
        int b;
        char a;
	int tq;
	int count = 0;
        int i = 0;
        int j = 0;
        int flag1 = 0, flag2 = 1;
	int temp1 = 0;
	int sq = 0;
	int st[10];
	awt = 0.0;
	swt = 0;
        if ((fp = fopen("FCFS.txt","r")) == NULL){
                printf("Error opening file\n");
        }


        while ((a = fgetc(fp)) != '#'){
                continue;
        }
        while (fscanf(fp,"%d",&b) != EOF){
                j++;
                if (flag1 == 0){
                        process[i].pid = b;
                        flag1 = 1;
                        flag2 = 0;
                }
                else if (flag2 == 0){
                        process[i].bt = b;
                        flag2 = 1;
                        flag1 = 0;
                        i++;
                }
        }
	fclose(fp);
	n = (j/2);
	printf("\n\n\n");
	printf("Round-Robin\n");
	printf("Entire the time quantum\n");
	scanf("%d",&tq);
	printf("Pid   Bursttime\n");
        for (i = 0;i < n; i++){
                  printf("%d\t%d\n", process[i].pid, process[i].bt);
		  st[i] = process[i].bt;
        }
	while (1){
		for (i = 0, count =0; i < n; i++){
			temp1 = tq;
			if (process[i].bt == 0){
				count++;
				continue;
			}
			if (process[i].bt > tq){
				process[i].bt =  process[i].bt - tq;
			}
			else if (process[i].bt >= 0){
				temp1 = process[i].bt;
				process[i].bt = 0; 
			}
			sq = sq + temp1;
			process[i].tat = sq;
		}
		if (n == count){
			break;
		}
	}
	for (i = 0; i < n; i++){
		process[i].wt = process[i].tat - st[i];
		printf("The waiting time for process %d is %d\n", i, process[i].wt);
		swt = swt + process[i].wt;
	}
	awt = (float)swt/n;
	printf("The average waiting time is %f\n", awt);
	
	return 0;
}
int SJFS()
{
	FILE *fp;
        int b;
        char a;
        int i = 0;
        int j = 0;
	int k = 0;
        int flag1 = 0, flag2 = 1;
        if ((fp = fopen("SJFS.txt","r")) == NULL){
                printf("Error opening file\n");
        }


        while ((a = fgetc(fp)) != '#'){
                continue;
        }
        while (fscanf(fp,"%d",&b) != EOF){
                j++;
                if (flag1 == 0){
                        process[i].pid = b;
                        flag1 = 1;
                        flag2 = 0;
                }
                else if (flag2 == 0){
                        process[i].bt = b;
                        flag2 = 1;
                        flag1 = 0;
                        i++;
                }
	}
	fclose(fp);
	printf("SJFS\n");
	n = (j/2);
        printf("Pid   Bursttime\n");
        for (i = 0;i < n; i++){
                  printf("%d\t%d\n", process[i].pid, process[i].bt);
        }
	for (i = 0; i < n; i++){
                for (k = i + 1; k < n; k++){
                        if (process[i].bt > process[k].bt){
                                temp = process[i];
                                process[i] = process[k];
                                process[k] = temp;
                        }
                }
        }
	printf("Sorted processes according to their busrt sime\n");
	printf("Pid   Bursttime\n");
        for (i = 0;i < n; i++){
                  printf("%d\t%d\n", process[i].pid, process[i].bt);
	}
	process[0].wt = 0;
        for (i = 1; i < n; i++){
                process[i].wt = process[i-1].wt + process[i-1].bt;
        }
        for (i = 0;i < n; i++){
                printf("The waiting time of process %d is %d\n", i, process[i].wt);
        }
        for (i = 0; i < n; i++){
                swt = swt + process[i].wt;
        }
        awt = (float)swt/n;
        printf("The average waiting time is %f\n", awt);
	
	return 0;
}  	
int main(void)
{	
	int choice;
	printf("1.FCFS\n2.Priority\n3.Round-Robin\n4.SJFS\n");
	printf("Enter your choice\n");
	scanf("%d", &choice);
	switch(choice){
		case 1 : FCFS();
			 break;
		case 2 : Priority();
			 break;
		case 3 : Round_robin();
			 break;
		case 4 : SJFS();
			 break;
		default : printf("Invalid CHoice\n");
			  exit(0);
	}
	
		
	return 0;
}
	
