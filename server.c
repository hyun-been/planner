#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "name.h"

#define PORT 12345 //포트 번호
#define MAX_SOCK 1024
#define SIZE 1024
//====헤더파일 include 필요====
void error_handling(char *message); //예외 처리 메서드
void *announce_clnt(void *arg); //클라이언트와 통신하는 메서드(read/write)
char msg[1024];
//====아래 메서드는 db, 관리모듈과 연결필요====
//====필요 시 인자 수정해서 사용하세요====
int register_id(char *id); //아이디 등록 메서드
int login(char *id, int clnt_sock); //로그인 메서드
char authNum[1];

int main()
{
        int serv_sock, clnt_sock; //클라이언트, 서버 소켓 변수
        struct sockaddr_in serv_addr, clnt_addr;
        socklen_t clnt_addr_size;
        pthread_t t_id;

        serv_sock=socket(AF_INET, SOCK_STREAM, 0);
        if(serv_sock==-1)
                error_handling("socket error");
        memset(&serv_addr,0,sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
        serv_addr.sin_port=htons(PORT);

        if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
                error_handling("bind error");

        if(listen(serv_sock,5)==-1)
                error_handling("listen error");

        listen(serv_sock, 5);

        //클라이언트 connect 완료 시 시작
        while(1)
        {
                clnt_sock=accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
                if(clnt_sock==-1)
                        error_handling("accept error");
                read(clnt_sock,msg,sizeof(msg)); //클라이언트로부터 온 메시지 읽음(아이피 주소)
                printf("접속:%s\n",msg); //메시지 출력
                pthread_create(&t_id, NULL, announce_clnt, (void *)&clnt_sock);
        }
        close(clnt_sock);
}
void error_handling(char* message) //예외 처리
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}
void *announce_clnt(void *arg) //클라이언트와 통신하는 메서드
{
        int clnt_sock=*((int*)arg);
        char start_option[1]; //옵션 저장하는 문자열
        FILE *fp; //파일 변수
        char authNum[1];
        int state; //프로그램 허용 여부 저장하는 변수
        char notice[]="\n===프로그램을 시작합니다===\n\n>>옵션을 선택하세요<<\n[1]사용자  등록\t[2]로그인\n|입력|";
        write(clnt_sock,notice,sizeof(notice)); //클라이언트에게 notice 정보 보냄

        while(1)
        {
                if(read(clnt_sock,start_option,sizeof(start_option))==-1) //클라이언트로부터 온 옵션 정보 읽음
                        error_handling("read error");

                if(strncmp(start_option,"1",1)==0) //옵션=1
                {
                        loadInfo();
                        char pro1[]="\n사용하실 아이디을 입력하세요\n";
                        char id[1024];
                        write(clnt_sock,pro1,sizeof(pro1)); //클라이언트에게 옵션1 안내문 보냄
                        read(clnt_sock,id,sizeof(id)); //클라이언트로부터 사용자 아이디 받음
		char name[1024];
		read(clnt_sock,name,sizeof(name));
		state=1;
		writeArr(id,name);
		saveInfo();
		strcpy(authNum,"1");
		//read(clnt_sock,authNum,sizeof(authNum));
                        break;
                }
                else if(strncmp(start_option,"2",1)==0) //옵션=2
                {
                        loadInfo();
                        char pro2[]="\n아이디를 입력하세요\n";
                        char id[1024];
                        write(clnt_sock,pro2,sizeof(pro2)); //클라이언트에게 옵션2 안내문 보냄


                        read(clnt_sock,id,sizeof(id)); //클라이언트로부터 아이디 받음
		printf("입력된 아이디: %s\n",id);
		//printf("recepted");
                        state=login(id, clnt_sock); //프로그램 허용 여부
		//printf("state=%d\n",state);
                        break;
                }
                else //잘못 입력한 경우
                {
                        char pro3[]="\n잘못된 입력입니다. 다시 옵션을 고르세요.\n|입력|";
                        write(clnt_sock,pro3,sizeof(pro3)); //클라이언트에게 경고문 보냄
                }
        }

        //====서버가 state를 write해서 클라이언트에 보내야 함====
        //프로그램 허용 여부에 따라 실행
        if(state) //사용허가(1)시 출력
        {
	printf("send menu to client\n");
                fp=fopen("menu.txt","r"); //메뉴 출력
                if(fp==NULL)
                        error_handling("Cannot find the file...");
                char menu[100];
                for(int i=0;i<8;i++) //메뉴 8줄
                {
                        fgets(menu,sizeof(menu),fp);
                        write(clnt_sock,menu,sizeof(menu)); //1줄씩 클라이언트에게 보냄
                      menu[0]='\n'; //문자열에 null대입
                }
                fclose(fp); //파일 닫음
	printf("end to sending menu\n");
        }
char ok[1];
        printf("파일 생성중\n");
        FILE* commonGoalList1 = fopen("commonGoalList.txt", "a");
        if (commonGoalList1 == NULL)
              printf("파일 %s에 문제가 발생했습니다.\n", "commonGoalList.txt");
        fclose(commonGoalList1);

        strcpy(ok,"1");
        write(clnt_sock,ok,sizeof(ok));


        printf("파일 보내는중\n");
        FILE* commonGoalList2 = fopen("commonGoalList.txt", "r");
        char buf[SIZE];
        if (commonGoalList2 == NULL)
              printf("파일 %s에 문제가 발생했습니다.\n", "commonGoalList.txt");
        else {
               while (1) {
                     if (fgets(buf, SIZE, commonGoalList2) != NULL)
                               write(clnt_sock, buf, sizeof(buf));
                     else{
                               write(clnt_sock, "0", sizeof("1"));
                               break;
                     }
                }
                fclose(commonGoalList2);
                printf("파일 보내기끝\n");
        }
}
//====관리모듈과의 연결 필요====
int login(char *id, int clnt_sock) //====사용 허가 1리턴/ 사용 허가 기각 0리턴하도록====
{
        int returnNum;
        returnNum=checkMember(id);
        if (returnNum==1) strcpy(authNum,"1");//스터디원
        else if (returnNum==0) strcpy(authNum,"0");//허가안됨
        else if(returnNum==2) strcpy(authNum,"2");
        write(clnt_sock, authNum, sizeof(authNum));
        if(strcmp(authNum,"1")==0||strcmp(authNum,"2")==0)
        {
                printf("적법한 사용자가 접속했습니다.\n");
                return 1;
        }
        else
        {
                printf("적법하지 않은 사용자가 접속해 클라이언트를 종료시켰습니다.\n");
                return 0;
        }
}

