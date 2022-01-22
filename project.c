#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu_option.h"

#define SIZE 1024

//함수 프로토타입
void scoreMenu();
void detailMenu();
void goalMenu(int,char*);
void makeGoalList(int);
void writeCommonProject(FILE*);
void writeIndivProject(FILE*);
void copyCommonGoal();
void copyIndivGoal();
void commonGoalNum();
void indivGoalNum();
void checkCommonGoal();
void checkIndivGoal();
void deleteCommonGoal();
void deleteIndivGoal();
void commonFinish();
void indivFinish();
void copyTemp(FILE *f1, FILE *f2);
double Point();
double commonProjectRate();
double indivProjectRate();
void countCommonGoalNum();
void countIndivGoalNum();

int countCommon=0;
int checkCountCommon=0;
int countIndiv=0;
int checkCountIndiv=0;

void detailMenu(){
        printf("\n\t1. 스터디 목표\n");
        printf("\t2. 나의 목표\n");
        printf("\t3. 뒤로 가기\n");
        printf("\t|입력|");
}

void scoreMenu(){
        printf("\n\t1. 스터디 목표 달성률\n");
        printf("\t2. 나의 목표 달성률\n");
        printf("\t3. 점수 확인\n");
        printf("\t4. 뒤로 가기\n");
        printf("\t|입력|");
}
void goalMenu(int clientTask, char* authNum) {
   switch (clientTask)
   {
                case 1: //목표 등록하기
                   while (1) {
                                detailMenu();
                                int answer;
                                scanf("%d", &answer);
                                char handling;
                                scanf("%c", &handling);
                                if (answer == 1) {
                                        if(strcmp(authNum,"1")==0){//조건 수정
                                                printf("\n접근 권한이 없습니다. 다른 메뉴를 선택하세요.\n");
                                                continue;
                                        }
                                        else{
                                                makeGoalList(1);
                                                printf("\n스터디 목표가 작성되었습니다.\n");
                                                printf("\n");
                                                break;
                                        }
                                }
                                else if (answer == 2) {
                                        makeGoalList(2);
                                        printf("\n나의 목표가 작성되었습니다.\n");
                                        printf("\n");
                                        break;
                                }
                                else if (answer == 3){
			printf("\n");
                                        break;
		}
                                else
                                printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
                        }
                        break;
                case 2: //남은 목표 확인하기
                        while (1) {
                                detailMenu();
                                int answer;
                                scanf("%d", &answer);
                                char handling;
                                scanf("%c", &handling);
                                if (answer == 1) {

                                        printf("\n");
                                        checkCommonGoal();
                                        printf("\n");
                                        break;
                                }
                                else if (answer == 2) {

                                        printf("\n");
                                        checkIndivGoal();
                                        printf("\n");
                                        break;
                                }
                                else if (answer == 3)
                                break;
                                else
                                printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
                        }
                        break;
                case 3: //달성한 목표 체크하기
                        while (1) {
                                detailMenu();
                                int answer;
                                scanf("%d", &answer);
                                char handling;
                                scanf("%c", &handling);
                                if (answer == 1) {
                                        deleteCommonGoal();
                                        break;
                                }
                                else if (answer == 2) {
                                        deleteIndivGoal();
                                        break;
                                }
                                else if (answer == 3)
                                break;
                                else
                         printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
                        }
                        break;
                case 4: //목표 달성 현황 확인하기
                        while(1){
                                scoreMenu();
                                int answer;
                                scanf("%d", &answer);
                                char handling;
                                scanf("%c", &handling);
                                if (answer == 1) {
			countCommonGoalNum();
                                        commonFinish();
                                        printf(">>스터디 목표 달성률 %.1f%%<<\n\n", commonProjectRate()*100);
                                        break;
                                }
                                else if (answer == 2) {
			countIndivGoalNum();
                                        indivFinish();
                                        printf(">>개인 목표 달성률 %.1f%%<<\n\n", indivProjectRate()*100);
                                        break;
                                }
                                else if (answer == 3){
                                        printf("\t|점수| %.1f\n",Point());
                                        break;
                                }
                                else if (answer == 4)
                                break;
                                else
                                printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
                        }
                        break;
      }
} //목표 관련 메뉴(1~3)

void makeGoalList(int num) {
        if (num == 1) {
                FILE* commonGoalList;
                commonGoalList = fopen("commonGoalList.txt", "w");
                fprintf(commonGoalList, "<Common Goal List>\n");
                writeCommonProject(commonGoalList);
                fclose(commonGoalList);
                commonGoalNum();
 	   copyCommonGoal();
        }
        else {
                FILE* goalList;
                goalList = fopen("indivGoalList.txt", "w");
                fprintf(goalList, "<My Goal List>\n");
                writeIndivProject(goalList);
                fclose(goalList);
                indivGoalNum();
	   copyIndivGoal();
        }
}

void writeCommonProject(FILE *fp) {
        while (1) {
                printf("\n몇 개의 목표를 등록하시겠습니까?\n");
                int num;
                scanf("%d", &num);
                char handling;
                scanf("%c", &handling);

                if (num > 25||num < 0)
                        printf("\n목표는 25개 이하로 정해주세요.\n");
                else {
                        countCommon = num;
                        printf("\n==목표를 입력해주세요==\n\n");
                        for (int i = 0; i < num; i++) {
                                printf("목표 %d번:",i+1);
                                char answer[50];
                                scanf("%[^\n]s", answer);
                                strcat(answer,"\n");
                                fputs(answer,fp);
                                char handling;
                                scanf("%c", &handling);
                        }
                        printf("\n\n==목표 입력이 완료되었습니다==\n\n");
                        break;
                }
        }
}

void writeIndivProject(FILE *fp) {
        while (1) {
                printf("\n몇 개의 목표를 등록하시겠습니까?\n");
                int num;
                scanf("%d", &num);
                char handling;
                scanf("%c", &handling);
                if (num > 25||num < 0)
                        printf("\n목표는 25개 이하로 정해주세요.\n");
                else {
                        countIndiv = num;
                        printf("\n==목표를 입력해주세요==\n\n");
                        for (int i = 0; i < num; i++) {
                                printf("목표 %d번:",i+1);
                                char answer[50];
                                scanf("%[^\n]s", answer);
                                strcat(answer,"\n");
                                fputs(answer,fp);
                                char handling;
                                scanf("%c", &handling);
                        }
                        printf("\n\n==목표 입력이 완료되었습니다==\n\n");
                        break;
                }
        }
}

void copyCommonGoal() {
        char ch;
        FILE* fp;
        fp = fopen("commonGoalList.txt", "r");
        FILE* commonGoalList = fp;
        if (fp == NULL) {
                printf("파일 %s에 문제가 발생했습니다.\n", "commonGoalList.txt");
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        FILE* checkCommonGoalList = fopen("checkCommonGoalList.txt", "w");
        if (checkCommonGoalList == NULL) {
                fclose(checkCommonGoalList);
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(commonGoalList)) != EOF)
                fputc(ch, checkCommonGoalList);

        fclose(commonGoalList);
        fclose(checkCommonGoalList);
}

void copyIndivGoal() {
        char ch;
        FILE* fp;
        fp = fopen("indivGoalList.txt", "r");
        FILE* indivGoalList = fp;
        if (fp == NULL) {
                printf("파일 %s에 문제가 발생했습니다.\n", "indivGoalList.txt");
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        FILE* checkIndivGoalList = fopen("checkIndivGoalList.txt", "w");
        if (checkIndivGoalList == NULL) {
                fclose(checkIndivGoalList);
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(indivGoalList)) != EOF)
                fputc(ch, checkIndivGoalList);
        fclose(indivGoalList);
        fclose(checkIndivGoalList);
}
void countCommonGoalNum(){
	FILE* commonGoalList = fopen("commonGoalList.txt", "r");
        char buf[SIZE];
        int i = 0;
        if (commonGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "commonGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, commonGoalList) != NULL) {
                                i++;
                        }
                        else
                                break;
                }
        }
        countCommon = i-1;
        fclose(commonGoalList);
}
void commonGoalNum() {
        FILE* commonGoalList = fopen("commonGoalList.txt", "r");
        char buf[SIZE];
        int i = 0;
        if (commonGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "commonGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, commonGoalList) != NULL) {
                                printf("%s", buf);
                                i++;
                        }
                        else
                                break;
                }
        }
        countCommon = i-1;
        fclose(commonGoalList);
}

void countIndivGoalNum(){
        FILE* indivGoalList = fopen("indivGoalList.txt", "r");
        char buf[SIZE];
        int i = 0;
        if (indivGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "indivGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, indivGoalList) != NULL) {

                                i++;
                        }
                        else
                                break;
                }
        }
        countIndiv = i-1;
        fclose(indivGoalList);
}

void indivGoalNum() {
        FILE* indivGoalList = fopen("indivGoalList.txt", "r");
        char buf[SIZE];
        int i = 0;
        if (indivGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "indivGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, indivGoalList) != NULL) {
                                printf("%s", buf);
                                i++;
                        }
                        else
                                break;
                }
        }
        countIndiv = i-1;
        fclose(indivGoalList);
}

void checkCommonGoal() {
        FILE* checkCommonGoalList = fopen("checkCommonGoalList.txt", "r");
        char buf[SIZE];
        int i=0, count=0;
        if (checkCommonGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "checkCommonGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, checkCommonGoalList) != NULL) {
                                if(count!=0)
                                printf("%d.",count);
                                printf("%s", buf);
                                i++,count++;
                        }
                        else
                                break;
                }
        }
        checkCountCommon = i-1;
        fclose(checkCommonGoalList);
}
void checkIndivGoal() {
        FILE* checkIndivGoalList = fopen("checkIndivGoalList.txt", "r");
        char buf[SIZE];
        int i=0, count=0;
        if (checkIndivGoalList == NULL)
                printf("파일 %s에 문제가 발생했습니다.\n", "checkIndivGoalList.txt");
        else {
                while (1) {
                        if (fgets(buf, SIZE, checkIndivGoalList) != NULL)  {
                                if(count!=0)
                                printf("%d.",count);
                                printf("%s", buf);
                                i++,count++;
                        }
                        else
                                break;
                }
        }
        checkCountIndiv = i-1;
        fclose(checkIndivGoalList);
}

void deleteCommonGoal() {
        char buf[SIZE];
        while (1) {
                printf("\n몇 번째 목표를 완료하셨나요? 종료하려면 0을 누르세요.\n");
                int answer;
                scanf("%d",&answer);
                char handling;
               scanf("%c", &handling);
                if (answer > checkCountCommon)
                        printf("당신의 현재 남은 목표는 %d개입니다. 다시 입력해주세요.\n", checkCountCommon);
                else if (answer == 0)
                        break;
                else if (answer < 0)
                        printf("잘못 입력하셨습니다. 0이상의 수로 답해주세요.\n");
                else {
                        FILE* checkCommonGoalList = fopen("checkCommonGoalList.txt", "r");
                        FILE* temp=fopen("tempCommon.txt", "w");
                        FILE *gar=fopen("garbage.txt","w");
                        for(int i=0; i<=checkCountCommon; i++){
                                if(i==answer){
                                        fgets(buf,SIZE,checkCommonGoalList);
                                        fputs(buf,gar);
                                }
                                else{
                                        fgets(buf,SIZE,checkCommonGoalList);
                                        fputs(buf,temp);
                                }
                        }
                        fclose(gar); fclose(temp); fclose(checkCommonGoalList);
                        FILE* from=fopen("tempCommon.txt", "r");
                        FILE* to = fopen("checkCommonGoalList.txt", "w");
                        copyTemp(from, to);
                        fclose(from);
                        printf("\n"); checkCommonGoal();
                }
        }
}

void deleteIndivGoal() {
        char buf[SIZE];
        while (1) {
                printf("\n몇 번째 목표를 완료하셨나요? 종료하려면 0을 누르세요.\n");
                int answer;
                scanf("%d",&answer);
                char handling;
                scanf("%c", &handling);
                if (answer > checkCountIndiv)
                        printf("당신의 현재 남은 목표는 %d개입니다. 다시 입력해주세요.\n", checkCountIndiv);
                else if (answer == 0)
                        break;
                else if (answer < 0)
                        printf("잘못 입력하셨습니다. 0이상의 수로 답해주세요.\n");
                else {
                        FILE* checkIndivGoalList = fopen("checkIndivGoalList.txt", "r");
                        FILE* temp=fopen("tempIndiv.txt", "w");
                        FILE *gar=fopen("garbage.txt","w");
                        for(int i=0; i<=checkCountIndiv; i++){
                                if(i==answer){
                                        fgets(buf,SIZE,checkIndivGoalList);
                                        fputs(buf,gar);
                                }
                                else{
                                        fgets(buf,SIZE,checkIndivGoalList);
                                        fputs(buf,temp);
                                }
                        }
                        fclose(gar); fclose(temp); fclose(checkIndivGoalList);
                        FILE* from=fopen("tempIndiv.txt", "r");
                    FILE* to = fopen("checkIndivGoalList.txt", "w");
                        copyTemp(from, to);
                        fclose(from);
                        printf("\n"); checkIndivGoal();
                }
        }
}

void copyTemp(FILE *f1, FILE *f2) {
        char ch;
        if (f1 == NULL) {
                printf("파일에 문제가 발생했습니다.\n");
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        if (f2 == NULL) {
                fclose(f2);
                printf("종료하려면 아무 키나 눌려주세요.");
                exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(f1)) != EOF)
                fputc(ch, f2);
        fclose(f2);
}

double commonProjectRate() {
        double rate = 1 - (double)checkCountCommon / countCommon;
        return rate;
}

void commonFinish() {
        printf("\n당신이 완료하신 스터디 목표는 %d개 중 %d개입니다.\n", countCommon, countCommon-checkCountCommon);
}

double indivProjectRate() {
        double rate = 1 - (double)checkCountIndiv / countIndiv;
        return rate;
}

void indivFinish() {
        printf("\n당신이 완료하신 나의 목표는 %d개 중 %d개입니다.\n", countIndiv, countIndiv-checkCountIndiv);
}

double Point() {
   double point = commonProjectRate() * 5 + indivProjectRate() * 5;
   return point;
}

