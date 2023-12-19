#include<stdio.h>

struct Query {
    char QueryID[3];
    int ArrivalTime;
    int BurstTime;
    int CompletionTime;
    int TotalTime;
} Faculty[120], Student[120], Mix[120];

int TimeQuantum=0, FacultyCount=0, StudentCount=0, MixCount=0, TotalQueries=0, Burst=120;
int TQ=0, WaitTime=0, TATime=0, counter=0, total, CTarr[120], maximumCT=0;

void InputsForProcess() {
    int QueryType, AT=1000, BT=0;
    ValidQuery:
    printf("\nEnter total number of Queries: ");
    scanf("%d", &TotalQueries);
    if(TotalQueries<=0 || TotalQueries>120) {
        printf("\nQueries cannot be <0 or >120!\n");
        goto ValidQuery;
    }
    else {
        TQ = TotalQueries;
        printf("\nEnter Time Quantum for each query: ");
        scanf("%d", &TimeQuantum);

        for(int i=0; i<TotalQueries; i++) {
            TryQuery:
            printf("\nType of Query (1 for Faculty, 2 for Student): ");
            scanf("%d", &QueryType);

            if(QueryType == 1) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Faculty[FacultyCount].QueryID[0]);
                FTime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1059) || (AT<1200 && AT>1159)) {
                    printf("\nEnter Correct Time!\n");
                    goto FTime;
                }
                else {
                    if (AT>=1000 && AT<1100) {
                        Faculty[FacultyCount].ArrivalTime = AT-1000;
                    }
                    else {
                        Faculty[FacultyCount].ArrivalTime = AT-1040;
                    }
                }
                FBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(Burst - BT < 0 || BT <= 0 || Faculty[FacultyCount].ArrivalTime + BT >= 120) {
                    if(BT<=0) {
                        printf("\nBurst Time cannot be less than 0\n");
                    }
                    else {
                        if (Burst-BT<=0) {
                            int choice;
                            printf("System will not have enough time to handle this Query because of high BurstTime."
                                "\nWant to change BurstTime? (1 : Yes; Else : No) ");
                            scanf("%d", &choice);
                            if(choice==1) { goto FBTime; }
                            else {
                                printf("\nOK. This query's all data will be lost\n");
                                goto TryQuery;
                            }
                        }
                        else {
                            printf("\nInvalid Burst time for corresponding Arrival Time\n");
                        }
                    }
                    printf("Please enter valid Burst Time\n");
                    goto FBTime;
                }
                else {
                    Faculty[FacultyCount].BurstTime = BT;
                }
                Burst -= BT;
                Faculty[FacultyCount].TotalTime = Faculty[FacultyCount].BurstTime;
                FacultyCount++;
            }
            else if(QueryType == 2) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Student[StudentCount].QueryID[0]);
                STime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1060) || (AT<1200 && AT>1160)) {
                    printf("\nEnter valid Time!\n");
                    goto STime;
                }
                else {
                    if (AT>=1000 && AT<1100) {
                        Student[StudentCount].ArrivalTime = AT-1000;
                    }
                    else {
                        Student[StudentCount].ArrivalTime = AT-1040;
                    }
                }
                SBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(Burst - BT < 0 || BT <= 0 || Student[StudentCount].ArrivalTime + BT >= 120) {
                    if(BT<=0) {
                        printf("\nBurst Time cannot be less than 0\n");
                    }
                    else {
                        if (Burst-BT<=0) {
                            int choice;
                            printf("\nSystem does not have enough time to handle this Query because of high BurstTime."
                                "\nWant to change BurstTime? (1 : Yes; Else : No) ");
                            scanf("%d", &choice);
                            if(choice==1) {
                                goto FBTime;
                            }
                            else {
                                printf("\nOK. This query's all data will be lost\n");
                                goto TryQuery;
                            }
                        }
                        else {
                            printf("\nInvalid Burst time for corresponding Arrival Time\n");
                        }
                    }
                    printf("Please enter valid Burst Time\n");
                    goto SBTime;
                }
                else {
                    Student[StudentCount].BurstTime = BT;
                }
                Burst -= BT;
                Student[StudentCount].TotalTime = Student[StudentCount].BurstTime;
                StudentCount++;
            }
            else {
                printf("\nInvalid Input. Please try again.\n");
                goto TryQuery;
            }
        }
    }
}

int Fpartition(int low, int high) {
    int pivot = Faculty[high].ArrivalTime;
    int i = (low - 1);
    for (int j=low; j<=high; j++) {
        if (Faculty[j].ArrivalTime < pivot) {
            i++;
            Faculty[FacultyCount] = Faculty[i];
            Faculty[i] = Faculty[j];
            Faculty[j] = Faculty[FacultyCount];
        }
    }
    Faculty[FacultyCount] = Faculty[i+1];
    Faculty[i+1] = Faculty[high];
    Faculty[high] = Faculty[FacultyCount];
    return(i+1);
}

void FacultySort(int low, int high) {
    if(low < high) {
        int pi = Fpartition(low, high);
        FacultySort(low, pi-1);
        FacultySort(pi+1, high);
    }
}

int Spartition(int low, int high) {
    int pivot = Student[high].ArrivalTime;
    int i = (low - 1);
    for (int j=low; j<=high; j++) {
        if (Student[j].ArrivalTime < pivot) {
            i++;
            Student[StudentCount] = Student[i];
            Student[i] = Student[j];
            Student[j] = Student[StudentCount];
        }
    }
    Student[StudentCount] = Student[i+1];
    Student[i+1] = Student[high];
    Student[high] = Student[StudentCount];
    return(i+1);
}

void StudentSort(int low, int high) {
    if(low < high) {
        int pi = Spartition(low, high);
        StudentSort(low, pi-1);
        StudentSort(pi+1, high);
    }
}

void MergeQueries() {
    int iSC=0, iFC=0;
    if(FacultyCount !=0 && StudentCount !=0) {
        while(iSC < StudentCount && iFC < FacultyCount) {
            if(Faculty[iFC].ArrivalTime == Student[iSC].ArrivalTime) {
                Mix[MixCount] = Faculty[iFC];
                MixCount++;
                iFC++;
                Mix[MixCount] = Student[iSC];
                MixCount++;
                iSC++;
            }
            else if(Faculty[iFC].ArrivalTime < Student[iSC].ArrivalTime) {
                Mix[MixCount] = Faculty[iFC];
                MixCount++;
                iFC++;
            }
            else if(Faculty[iFC].ArrivalTime > Student[iSC].ArrivalTime) {
                Mix[MixCount] = Student[iSC];
                MixCount++;
                iSC++;
            }
        }
        if(MixCount != (FacultyCount + StudentCount)) {
            if(FacultyCount != iFC) {
                while(iFC != FacultyCount) {
                    Mix[MixCount] = Faculty[iFC];
                    MixCount++;
                    iFC++;
                }
            }
            else if(StudentCount != iSC) {
                while(iSC != StudentCount) {
                    Mix[MixCount] = Student[iSC];
                    MixCount++;
                    iSC++;
                }
            }
        }
    }
    else if(FacultyCount == 0) {
        while(iSC != StudentCount) {
            Mix[MixCount] = Student[iSC];
            MixCount++;
            iSC++;
        }
    }
    else if(StudentCount == 0) {
        while(iFC != FacultyCount) {
            Mix[MixCount] = Faculty[iFC];
            MixCount++;
            iFC++;
        }
    }
}

void RoundRobin() {
    total = Mix[0].ArrivalTime;
    printf("\n==> Time is in minutes for all calculations\n");
    printf("\nQuery ID\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\tCompletionTime\n");
    for(int i = 0; TQ != 0;) {
        if(Mix[i].TotalTime <= TimeQuantum && Mix[i].TotalTime > 0) {
            total = total + Mix[i].TotalTime;
            Mix[i].TotalTime = 0;
            counter = 1;
        }
        else if(Mix[i].TotalTime > 0) {
            Mix[i].TotalTime -= TimeQuantum;
            total = total + TimeQuantum;
        }
        if(Mix[i].TotalTime == 0 && counter == 1) {
            TQ--;
            int ATCalc = Mix[i].ArrivalTime+1000;
            int CTCalc = total+1000;
            CTarr[i] = CTCalc;
            if(ATCalc>1059) {
                ATCalc += 40;
            }
            if(CTCalc>1059) {
                CTCalc += 40;
            }
            printf("\n%s\t\t%d hh:mm\t%d minutes\t%d minutes\t%d minutes\t%d hh:mm",
                Mix[i].QueryID, ATCalc, Mix[i].BurstTime,
                total-Mix[i].ArrivalTime-Mix[i].BurstTime, total-Mix[i].ArrivalTime, CTCalc);
            WaitTime += total - Mix[i].ArrivalTime - Mix[i].BurstTime;
            TATime += total - Mix[i].ArrivalTime;
            counter = 0;
        }
        if(i == TotalQueries - 1) {
            i = 0;
        }
        else if(Mix[i+1].ArrivalTime <= total) {
            i++;
        }
        else {
            i = 0;
        }
    }
}

void MaxCT() {
    maximumCT = CTarr[0];
    for(int i=1; i<MixCount; i++) {
        if(maximumCT < CTarr[i]) {
            maximumCT = CTarr[i];
        }
    }
}

void PrintResult() {
    MaxCT(); total = Mix[0].ArrivalTime;
    printf("\n\nSummary of Execution: \n\n");
    printf("Total Time Spent on handling Queries: %d minutes\n", maximumCT-total-1000);
    float avgWaitTime = WaitTime * 1.0 / TotalQueries;
    float avgTATime = TATime * 1.0 / TotalQueries;
    printf("Average TurnAround Time : %.2f minutes\n", avgTATime);
    printf("Average Waiting Time : %.2f minutes", avgWaitTime);
    printf("\n\nProgram Execution Completed!\n\n");
}

int main() {
    printf("\n\t\tWelcome to the OS Project\n\n"
        "Please follow these instructions to execute the program:\n"
        "1. Enter number of queries between 0 & 120\n"
        "2. Make sure to keep value of TimeQuantum minimum for convenience\n"
        "3. Enter Query Arrival Time in the format of HHMM\n"
        "    Example: 10:25 should be entered as 1025\n"
        "4. Next Query's ArrivalTime must be less than previous Query's CompletionTime (ArrivalTime + BurstTime)\n"
        "5. BurstTime must be entered such that (ArrivalTime + BurstTime) < 120\n");
    InputsForProcess();
    FacultySort(0, FacultyCount-1);
    StudentSort(0, StudentCount-1);
    MergeQueries();
    RoundRobin();
    PrintResult();
}
