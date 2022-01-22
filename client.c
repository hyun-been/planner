#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "menu_option.h"
#include "name.h"

//====헤더파일 include 필요====
void error_handling(char* message); //예외 처리
void program(int clnt_sock); //프로그램 실행(메뉴 출력+옵션 함수 호출)
void execute_opt(int option); //프로그램 옵션 실행


char authNum[1];//인증번호 받음

int main(int argc, char* argv[])
{
        int clnt_sock; //클라이언트 소켓
        struct sockaddr_in serv_addr;
        char msg[1024];
        char start_option[1]; //시작 옵션 저장하는 문자열

        clnt_sock=socket(PF_INET, SOCK_STREAM, 0);
        if(clnt_sock==-1)
                error_handling("socket error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
        serv_addr.sin_port=htons(atoi(argv[2]));

        if(connect(clnt_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
                error_handling("connect error");

        //서버 accept 완료 시 실행
        write(clnt_sock, argv[1], strlen(argv[1])+1); //서버에게 아이피 번호 보냄

        while(1)
        {
                if(read(clnt_sock, msg, sizeof(msg))==-1) //서버로부터온 안내문 읽음
                        error_handling("read error");
                printf("%s", msg); //안내문 출력
                if(strcmp(start_option,"1")==0||strcmp(start_option,"2")==0) //시작옵션이 1 or 0이면 무한루프 빠져나옴
                        break;
                start_option[0]='\0'; //시작옵션에 null대입
                scanf("%s",start_option); //사용자로부터 시작옵션 입력받음
                write(clnt_sock, start_option, sizeof(start_option)); //서버에게 사용자 옵션 보냄
                msg[0]='\0'; //메시지에 null대입
        }

        if(strcmp(start_option,"1")==0) //옵션=1
        {
                char idArr[100];
	int state;
	state=1;
	strcpy(idArr,signUp());

           write(clnt_sock, idArr, sizeof(idArr)); //서버에게 아이디 보냄
	char nameArr[1024];
	strcpy(nameArr,setName());
	write(clnt_sock,nameArr,sizeof(nameArr));
	strcpy(authNum,"1");
	writeArr(id,name);
	saveInfo();
	//write(clnt_sock,authNum,sizeof(authNum));
	
        }
        else //옵션=2
        {
                char idArr[100];
              scanf("%s",idArr); //사용자가 자신의 아이디 입력

                write(clnt_sock, idArr, sizeof(idArr)); //서버에게 아이디 보냄

	loadInfo();
	checkName(idArr);
        read(clnt_sock, authNum, sizeof(authNum));
	}
	

        if(strcmp(authNum,"1")==0||strcmp(authNum,"2")==0){
                printf("\n로그인되었습니다.\n\n");
	loadInfo();
                program(clnt_sock); //프로그램 실행
        }
        else
                printf("\n입력한 아이디는 존재하지 않는 아이디 입니다.\n프로그램을 종료합니다.\n");

        close(clnt_sock);
        return 0;
}

void error_handling(char* message) //예외 처리
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}

void program(int clnt_sock) //프로그램 실행
{
        char menu[8][100]; //메뉴 저장하는 문자열
        int option=0; //프로그램 옵션 저장하는 변수
	char ok[1];
	//printf("starting menu print\n");
        for(int i=0;i<8;i++)
        {
                read(clnt_sock,menu[i],sizeof(menu[i])); //서버에서 온 메뉴 1줄씩 읽음
	}
        //printf("메뉴 저장끝\n파일 복사시작\n");
        read(clnt_sock, ok, sizeof(ok));

        if(strcmp(authNum,"1")==0 && strcmp(ok,"1")==0/*strcmp(authNum,"2")==0*/){
                int stop=0;
                //write(clnt_sock,authNum,sizeof(authNum));
                FILE* commonGoalList = fopen("commonGoalList.txt", "w");
                char buf[1024];
                while (1) {
                        read(clnt_sock, buf, sizeof(buf));
                        if(strcmp(buf,"0")==0)
                                break;
                        fputs(buf,commonGoalList);
                        buf[0]='\0';
                }
                fclose(commonGoalList);
        }

        while(1) //옵션이 7(종료)이 아닌 경우
        {
	for(int i=0;i<8;i++)
              	  printf("%s",menu[i]);
                printf("\n\t옵션을 입력하세요:");
                scanf("%d",&option); //옵션 입력 받아 저장
		char handling;
		scanf("%c",&handling);
                if(option<=0||option>7)
                        continue;
	if(option==7)
		break;
                execute_opt(option);

                
        }
	
}

void execute_opt(int option) //====스터디원 옵션 실행 함수====
{
   copyCommonGoal();

   switch(option)
   {
      case 1:
      case 2:
      case 3:
      case 4:   goalMenu(option,authNum);
                break;
      case 5: timeMenu();
            break;
      case 6: resetName();
            break;
   }
}

