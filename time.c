#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "menu_option.h"

void timeMenu();
int secToHour(int second);
int secToMin(int second);
int secToSec(int second);
void *t_function(void *);
void *m_function(void *);
void timer();
void subjectTimerMenu();

static int totalTime;
int subjectTime;
int sign;
int stop;

void timeMenu() {
    while (1) {
        printf("\n\t1. 공부한 시간 확인\n");
        printf("\t2. 공부 시작\n");
        printf("\t3. 타이머 초기화\n");
        printf("\t4. 종료\n");
        printf("\t|입력|");
        int answer1;
        char answer2;
        scanf("%d", &answer1);
        char handling;
        scanf("%c", &handling);

        if (answer1 == 1)
            printf("\n지금까지 공부한 시간은 %d시간 %d분 %d초입니다.\n", secToHour(totalTime), secToMin(totalTime), secToSec(totalTime));
        else if (answer1 == 2)
            subjectTimerMenu();
        else if (answer1 == 3)
            totalTime = 0;
        else if (answer1 == 4) {
            printf("\n타이머를 종료합니다.\n\n");
            break;
        }
        else {
            printf("잘못된 입력입니다. 1~3 중 하나를 입력해주세요.");
            continue;
        }

        answer2 = '\0';
        while (answer2 != 'y' & answer2 != 'n') {
            printf("\n뒤로 돌아가시겠습니까? (y/n)\n");
            scanf("%c", &answer2);
            char handling;
            scanf("%c", &handling);
            if (answer2 == 'y')
                break;
            else if (answer2 == 'n')
                break;
            else
                printf("잘못된 입력입니다. y/n 둘 중 하나를 입력해주세요.\n");
        }

        if (answer2 == 'y')
            continue;
        else
            break;
    }
}

int secToHour(int second) {
    int hour;
    hour = second / 3600;
    return hour;
}

int secToMin(int second) {
    int min;
    min = second % 3600 / 60;
    return min;
}

int secToSec(int second) {
    int sec;
    sec = second % 60;
    return sec;
}

void *t_function(void *data) {
	int id;
	int i = 0;
	id = *((int *)data);

	while(1) {
		if(stop==1){
			i=0; subjectTime=0;
			break;
		}
		sleep(1);
		i++;
		subjectTime = i;
		subjectTime++;
	}
}

void *m_function(void *data) {
	int id;
	int i = 0;
	id = *((int *)data);

	printf("타이머를 시작합니다.\n");
	while(1) {
		char answer;
		printf("타이머를 멈추기 위해서는 q를 눌려주세요.\n");
		scanf("%c", &answer);
		char handling;
		scanf("%c", &handling);
		if(answer == 'q') {
			sign = 0;
            break;
		}
        else
        	printf("잘못된 입력입니다.\n");
    }
}

void timer () {
	pthread_t p_thread[2];
	int thr_id;
	int status;
	int a = 1;
	int b = 1;
	
	stop=0;
	thr_id = pthread_create(&p_thread[0], NULL, m_function, (void *)&a);
	if(thr_id < 0) {	
		perror("thread create error: ");
		exit(1);
	}
	while (sign = 1) {
		thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);
		if(thr_id < 0) {
			perror("thread create error: ");
			exit(1);
		}
		if(sign != 1){
			printf("지금까지 공부한 시간은 %d시간 %d분 %d초입니다.\n", secToHour(subjectTime), secToMin(subjectTime), secToSec(subjectTime));
			pthread_detach(p_thread[0]);
			pthread_detach(p_thread[1]);
			totalTime += subjectTime;
			stop=1;
			break;
		}
	}
}

void subjectTimerMenu() {
    printf("\n무슨 과목을 공부할 것인가요 ? (1~5사이의 숫자로 입력해주세요.)\n");
    int answer;
    scanf("%d", &answer);
    char handling;
    scanf("%c", &handling);
    switch (answer) {
    case 1:
        timer();
        break;
    case 2:
        timer();
        break;
    case 3:
        timer();
        break;
    case 4:
        timer();
        break;
    case 5:
        timer();
        break;
    default:
        printf("잘못된 입력입니다.\n타이머를 종료합니다\n");
    }
}
