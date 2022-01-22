#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name.h"

char* errorArray[] = { "개새","씨발","젠장","좆","ㅆㅂ","ㅅㅂ","ㄲㅈ","염병","ㅈㅍ","꺼져","존나","ㅈㄴ","지랄","ㅈㄹ","똘추","빡추","니미","엠창","씹새","병신","ㅂㅅ" };

char* signUp() {
	loadInfo();

    while (1) {
        id = (char*)(malloc)(sizeof(char)*12);
	scanf("%s",id);
	getchar();
         if (strlen(id) > 12)
            printf("글자수가 초과되었습니다. 다시 입력해주세요.\n");
        else {
            if (num == 0){
		//printf("your the first member!");
                break;}
            else {
		//printf("not first\n");
                int ans = checkIDDuplicate(id);
                if (ans == 0) {
                    printf("이미 사용중인 아이디입니다. 다시 입력해주세요.\n");
                }
                else
                    break;
            }
        }
    }
    printf("아이디 등록에 성공했습니다.\n");

    return id;
}

char* setName() {
    while (1) {
        printf("\n사용하실 닉네임을 입력하세요.\n");
        name = (char*)(malloc)(sizeof(char) * 24);
        scanf("%s", name);
        getchar();
        if (num == 0)
            break;
        else {
            int ans = checkNameDuplicate(name);
            if (ans == 0)
                printf("이미 사용 중인 닉네임입니다. 다시 입력해주세요.\n");
            else
                break;
        }
    }
    errorCheck();
    printf("닉네임이 %s 로 설정되었습니다.\n", name);
	return name;
}

void currentName() {
    printf("\n현재 당신의 닉네임은 %s 입니다.\n", name);
}

void resetName() {
    currentName();
    while (1) {
        printf("닉네임을 변경 하시겠습니까? (Y/N)\n");
        char answer;
        scanf("%c", &answer);
        getchar();
        if (answer == 'y' || answer == 'Y') {
            setName();
            strcpy(nameArr[no], name);
            break;
        }
        else if (answer == 'n' || answer == 'N')
            break;
        else
            printf("잘못된 입력입니다. 다시 입력해주세요.\n");
    }
    strcpy(nameArr[no], name);
    saveInfo();
}

int checkIDDuplicate(char* id) {
    int ret = 0;
    for (int i = 0; i < num; i++) {
        ret = strcmp(id, idArr[i]);
        if (ret == 0)
            break;
    }
    return ret;
}

int checkNameDuplicate(char* name) {
    int ret = 0;
    for (int i = 0; i < num; i++) {
        ret = strcmp(name, nameArr[i]);
        if (ret == 0)
            break;
    }
    return ret;
}

void printErrorArray(char** arr, int size) {
    printf("\n금지어는 다음과 같습니다.\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

void errorCheck() {
    int i;
    char* ret;
    for (i = 0; i < sizeof(errorArray) / sizeof(errorArray[0]); i++) {
        ret = strstr(name, errorArray[i]);
        if (ret != NULL) {
            break;
        }
    }
    if (ret != NULL) {
        printf("\n입력하신 닉네임에 금지어가 포함되어 있으므로 새로운 닉네임을 입력해주세요.\n");
        printf("금지어: %s\n", errorArray[i]);
        char answer;
        while (1) {
            printf("금지어 목록 확인은 q, 닉네임 재설정은 r을 눌러주세요.\n");
            scanf("%c", &answer);
            getchar();
            if (answer == 'q' || answer == 'Q') {
                printErrorArray(errorArray, sizeof(errorArray) / sizeof(errorArray[0]));
            }
            else if (answer == 'r' || answer == 'R') {
                while (1) {
                    printf("\n사용하실 닉네임을 입력하세요. (닉네임은 최대 8문자까지 설정할 수 있습니다)\n");
                    scanf("%s", name);
                    getchar();
                    if (num == 0)
                        break;
                    else {
                        int ans = checkNameDuplicate(name);
                        if (ans == 0)
                            printf("이미 사용 중인 닉네임입니다. 다시 입력해 주세요.\n");
                        else
                            break;
                    }
                }
                errorCheck();
                break;
            }
            else
                printf("잘못된 선택입니다. 다시 선택해주세요\n");
        }
    }
}

void writeArr(char* id, char* name) {
    no = num;
    strcpy(idArr[no], id);
    strcpy(nameArr[no], name);
    num++;
}

void loadInfo() {
    if (num == 0) {
        FILE* idFile;
        FILE* nameFile;
        char iBuff[15];
        char* iptr;
        char nBuff[16];
        char* nptr;
        idFile = fopen("ID.txt", "r");
        nameFile = fopen("NAME.txt", "r");
        int i = 0;
        while (fgets(iBuff, sizeof(iBuff), idFile)) {
            iptr = strtok(iBuff, "\n");
            while (iptr != NULL) {
                strcpy(idArr[i], iptr);
                break;
            }
            i++;
        }
        int j = 0;
        while (fgets(nBuff, sizeof(nBuff), nameFile)) {
            nptr = strtok(nBuff, "\n");
            while (nptr != NULL) {
                strcpy(nameArr[j], nptr);
                break;
            }
            j++;
        }

        num = i;
        fclose(idFile);
        fclose(nameFile);
    }
    chiefID = idArr[0];
    chiefName = nameArr[0];
}

void saveInfo() {
    FILE* idFile;
    FILE* nameFile;
    idFile = fopen("ID.txt", "w");
    nameFile = fopen("NAME.txt", "w");
    if (idArr != NULL && nameArr != NULL) {
        int i = 0;
        for (i = 0; i < num; i++) {
            fprintf(idFile, "%s\n", idArr[i]);
        }
        int j = 0;
        for (j = 0; j < num; j++) {
            fprintf(nameFile, "%s\n", nameArr[j]);
        }
    }
    fclose(idFile);
    fclose(nameFile);
}

void checkName(char* checkId){
    int ret = 0;
    for (int i = 0; i<num; i++){
	ret = strcmp(checkId, (char*)idArr[i]);
	if(ret==0){
		name=nameArr[i];
		no=i;
		break;
	}
    }

}
