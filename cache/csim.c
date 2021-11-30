#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

typedef struct line {
    int valid;
    int tag;
    int time;
} line;

typedef struct set {
    line* lines;
} set;
        
set* sets;
int num_sets, num_lines, set_bits, block_bits;
int hits, misses, evictions;

int main(int argc, char *argv[]) {
    FILE* file = 0;
    for (int opt; (opt = getopt(argc, argv, "s:E:b:t:")) != -1;) {
        switch (opt) {
        case 's':
            set_bits = atoi(optarg);
            num_sets = 2 << set_bits;
            break;
        case 'E':
            num_lines = atoi(optarg);
            break;
        case 'b':
            block_bits = atoi(optarg);
            break;
        case 't':
            file = fopen(optarg, "r");
            if (file == NULL) return 1;
            break;
        }
    }


    sets = malloc(sizeof(set) * num_sets);
    for (int i = 0; i < num_sets; ++i) {
        sets[i].lines = malloc(sizeof(line) * num_lines);
        memset(sets[i].lines, 0, sizeof(line*) * num_lines);
    }
    
    char q, w;
    int address, size;
    int ts = 1;
    while (fscanf(file, " %c%x%c%d", &q, &address, &w, &size) != EOF) {
        if (q == 'I') continue;

        for (int tc = 1 + (q == 'M'); tc--;) {
            size_t set_idx = (address >> block_bits) & ((1 << set_bits) - 1);
            int tag = (address >> (set_bits + block_bits)) & 0xFFFFFFFF;
            
            set* s = sets + set_idx;
            int free_idx = -1;
            int br = 0;
            int ts_min = 987654321;
            int ts_idx = -1;

            for (int i = 0; i < num_lines; ++i) {
                // check if there is same tag -> hit
                if (s->lines[i].valid && s->lines[i].tag == tag) {
                    ++hits;
                    s->lines[i].time = ts++;
                    br = 1;
                    break;
                }
                // check if it has free space (not valid line)
                if (s->lines[i].valid == 0) {
                    free_idx = i;
                }
                else {
                    if (s->lines[i].time < ts_min) {
                        ts_idx = i;
                        ts_min = s->lines[i].time;
                    }
                }
            }
            if (br) continue;
            // miss -> evict
            if (free_idx == -1) {
                ++misses;
                ++evictions;
                s->lines[ts_idx].tag = tag;
                s->lines[ts_idx].time = ts++;
            }
            // miss -> put it on free space
            else {
                ++misses;
                s->lines[free_idx].tag = tag;
                s->lines[free_idx].valid = 1;
                s->lines[free_idx].time = ts++;
            }
        }
    }
    printSummary(hits, misses, evictions);
}
