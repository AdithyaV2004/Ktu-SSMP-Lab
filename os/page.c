#include <stdio.h>
int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int findLFU(int freq[], int n) {
    int i, min = freq[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (freq[i] < min) {
            min = freq[i];
            pos = i;
        }
    }
    return pos;
}
void FIFO(int pages[], int n, int framesCount) {
    int frames[10], i, j = 0, pageFaults = 0;
    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nPage Replacement using FIFO:\n");
    for (i = 0; i < n; i++) {
        int flag = 0;
        for (int k = 0; k < framesCount; k++) {
            if (frames[k] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            frames[j] = pages[i];
            j = (j + 1) % framesCount;
            pageFaults++;
        }
        printf("Page %d -> ", pages[i]);
        for (int k = 0; k < framesCount; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
void LRU(int pages[], int n, int framesCount) {
    int frames[10], time[10], counter = 0, i, j, flag1, flag2, pos, pageFaults = 0;
    for (i = 0; i < framesCount; i++)
        frames[i] = -1;

    printf("\nPage Replacement using LRU:\n");
    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            for (j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0) {
            pos = findLRU(time, framesCount);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }
        printf("Page %d -> ", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
void LFU(int pages[], int n, int framesCount) {
    int frames[10], freq[10], i, j, pos, pageFaults = 0;
    for (i = 0; i < framesCount; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }
    printf("\nPage Replacement using LFU:\n");
    for (i = 0; i < n; i++) {
        int flag = 0;
        for (j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                flag = 1;
                break;
            }
        }
        if (!flag) {
            int empty = -1;
            for (j = 0; j < framesCount; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }
            if (empty != -1) {
                frames[empty] = pages[i];
                freq[empty] = 1;
                pageFaults++;
            } else {
                pos = findLFU(freq, framesCount);
                frames[pos] = pages[i];
                freq[pos] = 1;
                pageFaults++;
            }
        }
        printf("Page %d -> ", pages[i]);
        for (j = 0; j < framesCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults = %d\n", pageFaults);
}
int main() {
    int pages[30], n, framesCount, choice;  
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &framesCount);
    do {
        printf("\n--- Page Replacement Menu ---\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. LFU\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: FIFO(pages, n, framesCount); break;
            case 2: LRU(pages, n, framesCount); break;
            case 3: LFU(pages, n, framesCount); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
    return 0;
}
