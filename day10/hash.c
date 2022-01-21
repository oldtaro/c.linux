#include <stdio.h>
#include <stdlib.h>
#define MaxSize 13 //表长取质数减少冲突

int Hashkey(char* c) {
	int h = 0, g, i = 0;
	while (c[i]) {
		h = (h << 4) + c[i++];
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MaxSize;
}

int main() {
	char* pstr[5] = { "hello","world","how","are","you" };
	char* hashtable[MaxSize] = {0};
	int i;
	for (i = 0; i < 5; i++) {
		int k = Hashkey(pstr[i]);
		printf("字符串：%-6s，hash值：%2d\n", pstr[i], k);
		hashtable[k]= pstr[i];
	}
	for (i = 0; i < MaxSize; i++) {
		printf("hash表 %2d内容：%-6s\n", i, hashtable[i]);
	}
	system("pause");
	return 0;
}