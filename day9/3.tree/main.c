#include "func.h"

int main() {
	int i;
	BiNode* b[10];
	printf("����˳��\n");
	for (i = 0; i < 10; i++) {
		b[i] = (BiNode*)calloc(1, sizeof(BiNode));
		b[i]->data = i;
		printf("%2d", i);
	}
	int j = 0;
	for (i = 1; i < 10; i++) {
		if (b[j]->left == NULL) {
			b[j]->left = b[i];
		}
		else if (b[j]->right == NULL) {
			b[j++]->right = b[i];
		}
	}
	printf("\n�������\n");
	midOrder(b[0]);
	system("pause");
}