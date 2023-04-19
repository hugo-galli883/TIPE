#include <stdio.h>
#include <stdlib.h>
#include "dyn-tables.h"

struct neural {
    int id;
    float weight;
    int* input;
    struct neural** output;
};
typedef struct neural neural;

struct layer {
    int n; //Number of neurals stockables in the layer (and depht of the "table" table)
    int f; //Numbers of neurals actually in the layer ("f" for "fill")
    neural** table; //Table of neural's address'
};
typedef struct layer layer;

struct neural_network {
    int depht; //Depth of the neural network (and length of the "dephts" table)
    neural* elements;
    layer** dephts; //Table containing address to layers
};
typedef struct neural_network n_n;

neural *new_neural() {
    neural* n = malloc(sizeof(neural));
    n->id = 1;
    n->weight = 0.8;
    n->input = malloc(1*sizeof(int));
    n->input[0] = 0;
    n->output = malloc(1*sizeof(neural));
    n->output[0] = NULL;
    return n;
}

layer* new_layer(int n) {
    layer* l = malloc(sizeof(layer));
    neural** a = malloc(n*sizeof(neural));
    for(int i = 0 ; n >i ; i++) {
        a[i] = new_neural();
    }
    l->table = a;
    l->f = 2;
    l->n = n;
    return l;
}

n_n* new_n_n(int d) {
    n_n* nn1 = malloc(sizeof(n_n));
    neural* t = malloc(2*d*sizeof(neural));
    nn1->depht = d;
    for(int i = 0 ; 2*d > i ; i++) {
        t[i] = NULL;
    }
    nn1->elements = t;
    nn1->dephts = malloc((d+1) * sizeof(layer));
    for (int i = 1 ; (d+1) > i ; i++) {
        nn1->dephts[i] = new_layer(2);
    }
    return nn1;
}

int delete_neural(neural* n) {
    printf("\tDeleting neural at address %p\n",n);
    free(n->input);
    printf("\t\tDeleting neural's input at address : %p\n\n",n->input);
    free(n->output);
    printf("\t\tDeleting neural's output at address : %p\n\n",n->output);
    free(n);
    return 1;
}

int add_neural(int d, n_n* nn) {
    if((nn->dephts[d]->f) >= nn->dephts[d]->n) {
        printf("Layer already full. Adding new space to add the new neural\n");
        int n = (nn->dephts)[d]->n;
        neural** a = malloc(2*n*sizeof(neural));
        for(int i = 0 ; n > i ; i++) {
            printf("\tCopying case N %d\n",i);
            a[i] = (nn->dephts)[d]->table[i];
        }
        for(int i = n ; (2*n)+2 > i ; i++) {
            printf("\tFilling case N %d with NULL pointer\n",i);
            a[i] = NULL;
        }
        free((nn->dephts)[d]->table);
        (nn->dephts)[d]->table = a;
        (nn->dephts)[d]->n = 2 * n;
        printf("\tNew size of the table : %d\n",(nn->dephts)[d]->n);
    }
    (nn->dephts)[d]->f ++;
    neural* n = new_neural();
    (nn->dephts)[d]->table[((nn->dephts)[d]->f)-1] = n;
    printf("New neural added :\n\tIndex : %d\n\tPointer : %p\n",((nn->dephts)[d]->f)-1,n);
    return 1;
}

int end_program(n_n* nn) {
    printf("Ending the program :\n");
    int d = nn->depht;
    for(int i = 1 ; d+1 > i ; i++) { //Loop that take over all the layers
        printf("Entering depht %d\n",i);
        for(int j = 0 ; ((nn->dephts[i])->n) > j ; j++) { //Loop taking over all the neurals of the selected layer
            // for(int k = 0 ; (nn->dephts[i]))
            printf("\tDeleting neural %d\n",j);
            if(((nn->dephts)[i]->table)[j] == NULL) {
                printf("\tNo neural\n");
                } else {
                delete_neural(((nn->dephts)[i]->table)[j]);
                // printf("\tNeural %d state :\n\t\tInput : %p\n\t\tOutput : %p\n\t\tWeight : %f\n\t\tId : %d\n\n",j,n->input,n->output,n->weight,n->id);
            }
        }
        free((nn->dephts)[i]->table);
        free((nn->dephts)[i]);
    }
    free(nn->dephts);
    free(nn);
    return 1;
}

int show_state(n_n* nn) {
    printf("Sowing state of n_n : %p\n",nn);
    int d = nn->depht;
    for(int i = 1 ; d+1 > i ; i++) { //Loop that take over all the layers
        printf("Entering depht %d address %p\n",i,(nn->dephts[i]));
        for(int j = 0 ; ((nn->dephts[i])->n) > j ; j++) { //Loop taking over all the neurals of the selected layer
            neural *n = nn->dephts[i]->table[j];
            if(n == NULL) {
                printf("\tNo neural %d\n",j);
            } else {
                printf("\tNeural %d state :\n\t\tInput : %p\n\t\tOutput : %p\n\t\tWeight : %f\n\t\tId : %d\n\n",j,n->input,n->output,n->weight,n->id);
            }
        }
    }
    return 1;
}

int link(neural* n1, neural* n2) {
    return 1;
}

int main () {
    int depht = 3; //Define the neural network's depht
    n_n* nn = new_n_n(depht);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    add_neural(2, nn);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    add_neural(2, nn);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    add_neural(2, nn);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    add_neural(2, nn);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    add_neural(2, nn);
    printf("Filling : %d\nTotal available : %d\n\n", nn->dephts[2]->f,nn->dephts[2]->n);
    show_state(nn);
    end_program(nn);
    return 1;
}

/*
1) Ajout d'une structure de tabeau dynamique


*/
