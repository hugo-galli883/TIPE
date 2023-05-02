#include <stdio.h>
#include <stdlib.h>
#include "dyn-tables.h"
//#include "neurals.c" //Included in the 'main.c' file

//  Neural dynamic table

n_dt* new_ndt() {
    n_dt* dt = malloc(sizeof(n_dt));
    dt->capacity = 2;
    dt->filling = 0;
    dt->table = malloc(2*sizeof(void*));
    dt->table[0] = NULL;
    dt->table[1] = NULL;
    return dt;
}

int add_ndt (n_dt* t, void* n) {
    if(t->filling >= t->capacity) {
        // printf("Resizing the dt\n");
        int c = t->capacity;
        void** tb = malloc(2 * c * sizeof(void*));
        for(int i = 0 ; c > i ; i++) {
            // printf("\tCopying element %d\n",i);
            tb[i] = t->table[i];
        }
        for(int i = c ; 2*c-1 >= i ; i++) {
            // printf("\tAdding pointer NULL at index %d\n",i);
            tb[i] = NULL;
        }
        free(t->table);
        // printf("\tOld table destroyed\n");
        t->table = tb;
        t->capacity = 2*c;
        // printf("\tNew table successfully assigned\n");
    }
    t->table[t->filling] = n;
    t->filling ++;
    return 1;
}

int delete_ndt(n_dt* ndt) {
    free(ndt->table);
    free(ndt);
    return 1;
}

int remove_el_ndt(n_dt* ndt, void* n) {
    int stop = 0;
    int i = 0;
    while(stop == 0 && ndt->filling > i) {
        if(ndt->table[i] == n) {
            stop = 1;
            ndt->table[i] = NULL;
            ndt->filling --;
        }
    }
    return 1;
}

int remove_id_ndt(n_dt* ndt, int n) {
    ndt->table[n] = NULL;
    ndt->filling --;
    return 1;
}

// int hard_dlt_ndt(n_dt* ndt) {
//     void** tb = ndt->table;
//     for(int i = 0 ; ndt->filling > i ; i++ ) {
//         delete_neural(tb[i]);
//     }
//     free(tb);
//     free(ndt);
//     return 1;
// }

int explore_ndt(n_dt* ndt) {
    printf("Exploring dt %p\n",ndt);
    for(int i = 0 ; ndt->filling > i ; i++) {
        printf("\tPointer %d : %p\n",i,ndt->table[i]);
    }
    return 1;
}
