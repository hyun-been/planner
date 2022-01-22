#define MEMBER 15
#include <stdio.h>

char* name;
char* id;
char nameArr[MEMBER][8];
char idArr[MEMBER][12];
char* chiefID;
char* chiefName;
char* signUp();
char* setName();
void resetName();

void currentName();

int checkIDDuplicate(char* cid);
int checkNameDuplicate(char* cname);
void printErrorArray(char** arr, int size);
void errorCheck();
void writeArr(char* wid, char* wname);

void saveInfo();
void loadInfo(); // 이걸 제일 먼저 실행해줘야 num이 정의되고 파일이 생기고.. 그리고 이걸 서버에 저장해두고
int no; // 클라이언트 프로그램 각각에 저장되어야 함. 멤버 번호? 같은 거임. 이걸로 닉네임 수정 등 할 수 있음.

int num;
int checkMember(char* checkId);
void checkName(char* checkId);
