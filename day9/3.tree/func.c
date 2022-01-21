#include "func.h"

void midOrder(BiTree p) {
	if (p == NULL) return;
	midOrder(p->left);
	printf("%2d", p->data);
	midOrder(p->right);
}
void enqueue(queue* pq) {

}
 