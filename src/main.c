#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>


#define WIDTH   150
#define HEIGHT  50
#define SLEEP   100000

#define DEAD_CELL_CHAR ' '
#define LIVE_CELL_CHAR '#'

#define xfree(p) { free((p)); (p) = NULL; }

static volatile sig_atomic_t running = 1;

struct Table {
    size_t xs;
    size_t ys;
    char **nodes;
};


void printTable(struct Table *t);
int  initTable(struct Table *t);
void deinitTable(struct Table *t);
long rangeRandNum(long low, long top);
char getCell(struct Table *t, long y, long x);
void updateCell(struct Table *t, long y, long x);
void setupGame(struct Table *t);
void gameMainLoop(struct Table *t);
void sigintHandler(int _) {
    (void)_;
    running = 0;
    printf("\nStopped!\n");
}


int main(void) {
    int err;
    srand(time(NULL));
    struct Table t = {
        .ys = HEIGHT,
        .xs = WIDTH,
        .nodes = NULL,
    };

    err = initTable(&t);
    if (err) {
        fprintf(stderr, "[ERROR] initializing game table failed\n");
        deinitTable(&t);
        return 1;
    }

    signal(SIGINT, sigintHandler);
    gameMainLoop(&t);

    deinitTable(&t);
    return 0;
}



void printTable(struct Table *t) {
    int cell_state;
    for (long y = 0; y < (long)t->ys; y++) {
        for (long x = 0; x < (long)t->xs; x++) {
            cell_state = getCell(t, y, x);
            if (cell_state)
                printf("%c", LIVE_CELL_CHAR);
            else
                printf("%c", DEAD_CELL_CHAR);
        }
        printf("\n");
    }
}


int  initTable(struct Table *t) {
    t->nodes = calloc(t->ys, sizeof(char*));
    if (t->nodes == NULL)
        return 1;
    for (long i = 0; i < (long)t->ys; i++) {
        t->nodes[i] = calloc(t->xs, sizeof(char));
        if (t->nodes[i] == NULL)
            return 1;
    }
    return 0;
}


void deinitTable(struct Table *t) {
    for (long i = 0; i < (long)t->ys; i++) {
        xfree(t->nodes[i]);
    }
    xfree(t->nodes);
}


long rangeRandNum(long low, long top) {
    void *p = malloc(1);
    long num = (((long)p + (long)rand()) % top) + low;
    xfree(p);
    return num;
}


char getCell(struct Table *t, long y, long x) {
    return ((y >= 0 && y < (long)t->ys)
            && (x >= 0 && x < (long)t->xs)) ? t->nodes[y][x] : -1;
}


void updateCell(struct Table *t, long y, long x) {
    int live_neighbors = 0;
    int curr_state = getCell(t, y, x);
    int tmp;

    if ((tmp = getCell(t, y+1, x)) != -1)
        if (tmp) live_neighbors++;
    if ((tmp = getCell(t, y+1, x+1)) != -1)
        if (tmp) live_neighbors++;
    if ((tmp = getCell(t, y+1, x-1)) != -1)
        if (tmp) live_neighbors++;

    if ((tmp = getCell(t, y-1, x)) != -1)
        if (tmp) live_neighbors++;
    if ((tmp = getCell(t, y-1, x+1)) != -1)
        if (tmp) live_neighbors++;
    if ((tmp = getCell(t, y-1, x-1)) != -1)
        if (tmp) live_neighbors++;

    if ((tmp = getCell(t, y, x-1)) != -1)
        if (tmp) live_neighbors++;
    if ((tmp = getCell(t, y, x+1)) != -1)
        if (tmp) live_neighbors++;


    if ((live_neighbors < 2 || live_neighbors > 3) && curr_state)
        t->nodes[y][x] = 0;
    if (live_neighbors == 3)
        t->nodes[y][x] = 1;
}


void setupGame(struct Table *t) {
    long x, iter;
    for (size_t y = 0; y < t->ys; y++) {
        for (iter = rangeRandNum(0, t->xs/5); iter > 0; iter--) {
            x = rangeRandNum(0, t->xs);
            t->nodes[y][x] = 1;
        }
    }
}


void gameMainLoop(struct Table *t) {
    setupGame(t);
    printf("\x1b[2J");
    while (running) {
        for (long y = 0; y < (long)t->ys; y++) {
            for (long x = 0; x < (long)t->xs; x++) {
                updateCell(t, y, x);
            }
        }
        printf("\x1b[d");
        printTable(t);
        usleep(SLEEP);
    }
}


#ifdef __cplusplus
}
#endif /* __cplusplus */
