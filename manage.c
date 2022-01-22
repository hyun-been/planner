#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int signIn(char* checkID); // 사용자 등록 확인, 권한에 따라 0,1,2 반환
int checkMember(char* checkID); // 스터디장 아닌 경우에 signIn에서 호출할 함수, 아이디에 매칭되는 닉네임 저장해줌
#include "name.h"
//서버에서만 실행


int checkMember(char* checkId) {
	int ret = 0;
	if(strcmp(checkId,"0000")==0){
		return 2;}
	else{
	for (int i = 1; i < num; i++) {
		ret = strcmp(checkId, (char*)idArr[i]);
		if (ret == 0) {
			name=nameArr[i];
			break;
		}
	}
	if (ret != 0)
		return 0;
	else
		return 1;
	}
}
