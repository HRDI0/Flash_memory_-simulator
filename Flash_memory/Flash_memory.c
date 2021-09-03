#include "Flash_memory.h"


int start() {
	FILE* fp;
	fopen_s(&fp, "memory.txt", "r");		//memory.txt 파일을 읽기 모드로 열기
	if (fp != NULL) {						//파일이 존재한다면
		char choice;
		while (1) {
			printf("Use last file? y/n : ");	//기존 파일을 그대로 사용할건지 새로 만들건지 결정
			scanf_s("%c", &choice);
			while (getchar() != '\n');
			switch (choice) {

			case 'y': {
				fclose(fp);
				return 0;
				break;
			}
			case 'n': {
				fclose(fp);
				return 1;
				break;
			}
			default:
				printf("\nPlease use only y or n\n");	//y와n 이외의 입력값은 예외처리한다.
				break;
			}
		}
	}
	else return 1;
	fclose(fp);	
}
void Init(int num) {
	printf("Flash memory size : ");
	memory = (BLOCK*)malloc(B_OF_MB*S_SIZE*D_SIZE);		//1MB 크기의 메모리를 할당한다.
	memset(memory->sector,32, B_OF_MB * S_SIZE * D_SIZE);	//할당된 메모리를 공백으로 초기화한다.
	if (memory == NULL) {
		printf("메모리 할당 실패!");					//메모리 할당 확인
		return;
	}
	
	FILE* fp;
	fopen_s(&fp,"memory.txt", "w+");						//memory.txt 파일을 쓰기모드로 열기/생성
	for (int i = 0; i < num; i++) {
		fprintf(fp, "%s\n", memory->sector);			//입력받은 크기만큼 메모장에 메모리 입력
	}
	fclose(fp);

	printf("%d byte memory\n", _msize(memory)*num);
	printf("Success\n");
	free(memory);										//할당된 메모리 할당해제
}
void write(int num, char data[]) {
	FILE* fp;
	int location = num * D_SIZE;						//메모리 파일을 '읽기'/쓰기 모드로 열기
	fopen_s(&fp, "memory.txt", "r+");	

	if (overwrite(fp,num) == 1) {						//입력받은 섹터번호의 위치에 데이터 유무 확인
		fseek(fp, location, SEEK_SET);					//입력받은 섹터번호의 위치로 이동
		fwrite(data, sizeof(char), sizeof(data), fp);	//해당 섹터에 데이터 입력
		fclose(fp);

		printf("write Sector %d success\n", num);
	}
	else return;
}
int overwrite(FILE *txt,int num) {						//입력받은 위치에 섹터에 데이터 유무 확인
	char buffer[D_SIZE];
	fseek(txt, (num * D_SIZE), SEEK_SET);
	fread(buffer, sizeof(buffer), 1, txt);
	if (buffer[0] != 32) {								//만약 해당 섹터에 데이터가 존재한다면 예외처리출력
		printf("error code 3 : (Over Write) \n");
		fclose(txt);
		return 0;
	}
	return 1;
}
void read(int num) {									//입력받은 섹터번호의 섹터 데이터 출력
	FILE* fp;
	char buffer[D_SIZE];
	fopen_s(&fp, "memory.txt", "r");					//메모리 파일을 읽기모드로 열기
	fseek(fp, (num * D_SIZE), SEEK_SET);				//입력받은 섹터번호의 위치로 이동
	fread(buffer, D_SIZE, 1, fp);						//해당 섹터의 데이터 읽기
	printf("%.*s",1, buffer);							//해당 섹터의 데이터 출력
	fclose(fp);
}
void erase(int num) {									//입력받은 섹터 번호의 섹터를 블록 단위로 지우기
	FILE* fp;
	char data[D_SIZE];									//지우기 처리를 위한 빈 데이터
	memset(data,32, D_SIZE);
	int num_Block = (num / S_SIZE);						//해당 섹터가 소속된 블록의 첫 번째 섹터 위치
	fopen_s(&fp, "memory.txt", "r+");					//메모리 파일을 '읽기'/쓰기 모드로 열기
	fseek(fp, (num_Block* S_SIZE * D_SIZE), SEEK_SET);			//해당 섹터의 소속 블록의 첫 번째 섹터로 이동
	for (int i = 0; i < S_SIZE; i++) {
		fwrite(data, D_SIZE, 1, fp);			//첫 번째 섹터부터 32번째 섹터까지 지우기 처리
	}
	fclose(fp);
	printf("erase Block %d success\n",num/S_SIZE);
}
void end() {
	exit(0);											//프로그램 종료
}
