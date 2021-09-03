#ifndef Flash_memory_h		//��������� ������ �ߺ� ȣ�� ���� �ʵ��� �Ѵ�.
#define Flash_memory_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define S_SIZE 32		//��� �� ������ ����
#define D_SIZE 512		//������ ũ��
#define B_OF_MB 64		//MB�� ����� ����

typedef struct block{		//����� �����ϱ� ���� ���� ����ü
	char sector[D_SIZE];
}BLOCK;

BLOCK* memory;			//1MB�� �Ҵ� �ϱ� ���� ���� ����ü ������

int start();			//�̹� �����ϴ� ������ Ȯ���ϰ� ���� ������ �״�� ���� �����ϴ� �Լ�
void Init(int num);		//�Է� ���� ũ�⸸ŭ �޸𸮸� �����ϴ� �Լ�
void write(int num, char data[]);	//���ϴ� ��ġ�� ���Ϳ� �����͸� �Է��ϴ� �Լ�
int overwrite(FILE *txt,int num);	//�̹� �����Ͱ� �ԷµǾ� �ִ� ���͸� �����Ͽ� ����ó���ϴ� �Լ�
void read(int num);		//���ϴ� ��ġ�� ���� �����͸� ����ϴ� �Լ�
void erase(int num);	//���ϴ� ��ġ�� ���͸� ��ϴ����� ����� �Լ�
void end();				//���α׷� ���� �Լ�

#endif /* Flash_memory_h */
#pragma once


