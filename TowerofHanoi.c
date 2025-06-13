#include <stdio.h>

int height = 0; 

void towersOfHanoi(int n, char from, char to, char aux) {
    if (n == 0)
        return;
    height++; 
    towersOfHanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    towersOfHanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    char src = 'S', dest = 'D', temp = 'T';
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    towersOfHanoi(n, 'S', 'D', 'T');
    printf("Total steps taken: %d\n", height);
    return 0;
}
