#include <stdio.h>
#include <stdlib.h>
#include "neurals.h"

neural *new_neural() {
    neural* n = malloc(sizeof(neural));
    n->id = 1;
    n->weight = 0.8;
    n->input = 1;
    n->output = new_ndt();
    return n;
}

layer* new_layer(int n, n_n* nn) {
    layer* l = malloc(sizeof(layer));
    neural** a = malloc(n*sizeof(neural));
    for(int i = 0 ; n >i ; i++) {
        a[i] = new_neural();
        add_ndt(nn->elements,a[i]);
    }
    l->table = a;
    l->f = 2;
    l->n = n;
    return l;
}

n_n* new_n_n(int d) {
    n_n* nn1 = malloc(sizeof(n_n));
    n_dt* t = new_ndt();
    nn1->depht = d;
    nn1->elements = t;
    nn1->dephts = malloc((d+1) * sizeof(layer));
    for (int i = 1 ; (d+1) > i ; i++) {
        nn1->dephts[i] = new_layer(2,nn1);
    }
    nn1->input = new_neural();
    nn1->end = new_neural();
    return nn1;
}

int delete_neural(neural* n) {
    // printf("\tDeleting neural at address %p\n",n);
    // printf("\t\tDeleting neural's output at address : %p\n\n",n->output);
    delete_ndt(n->output);
    free(n);
    return 1;
}

int add_neural(int d, n_n* nn) {
    if((nn->dephts[d]->f) >= nn->dephts[d]->n) {
        // printf("Layer already full. Adding new space to add the new neural\n");
        int n = (nn->dephts)[d]->n;
        neural** a = malloc(2*n*sizeof(neural));
        for(int i = 0 ; n > i ; i++) {
            // printf("\tCopying case N %d\n",i);
            a[i] = (nn->dephts)[d]->table[i];
        }
        for(int i = n ; (2*n) > i ; i++) {
            // printf("\tFilling case N %d with NULL pointer\n",i);
            a[i] = NULL;
        }
        free((nn->dephts)[d]->table);
        (nn->dephts)[d]->table = a;
        (nn->dephts)[d]->n = 2 * n;
        // printf("\tNew size of the table : %d\n",(nn->dephts)[d]->n);
    }
    (nn->dephts)[d]->f ++;
    neural* n = new_neural();
    (nn->dephts)[d]->table[((nn->dephts)[d]->f)-1] = n;
    add_ndt(nn->elements,n);
    // printf("New neural added :\n\tIndex : %d\n\tPointer : %p\n\n",((nn->dephts)[d]->f)-1,n);
    return 1;
}

int end_program(n_n* nn) {
    // printf("Ending the program :\n");
    int d = nn->depht;
    for(int i = 1 ; d+1 > i ; i++) { //Loop that take over all the layers
        // printf("Entering depht %d\n",i);
        for(int j = 0 ; ((nn->dephts[i])->n) > j ; j++) { //Loop taking over all the neurals of the selected layer
            // printf("\tDeleting neural %d\n",j);
            if(((nn->dephts)[i]->table)[j] == NULL) {
                // printf("\tNo neural\n");
                } else {
                delete_neural(((nn->dephts)[i]->table)[j]);
            }
        }
        free((nn->dephts)[i]->table);
        // printf("Deleting layer %d\n",i);
        free((nn->dephts)[i]);
    }
    free(nn->dephts);
    delete_ndt(nn->elements);
    delete_neural(nn->input);
    delete_neural(nn->end);
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
                printf("\tNeural %d state :\n\t\tInput : %f\n\t\tOutput :\n",j,n->input);
                for(int k = 0 ; n->output->filling > k ; k++) {
                    printf("\t\t\tOutput %d : %p\n",k+1,n->output->table[k]);
                }
                printf("\t\tWeight : %f\n\t\tId : %d\n\n",n->weight,n->id);
            }
        }
    }
    return 1;
}

int link(neural* n1, neural* n2) {
    add_ndt(n1->output, n2);
    return 1;
}

int add_input(neural* n, float x) {
    n->input += x;
    return 1;
}

int activate(neural* n) {
    for(int i = 0 ; n->output->filling >i ; i++) {
        add_input(n->output->table[i],(n->input) * (n->weight));
    }
    return 1;
}

int link_all(n_n* nn) {
    for(int i = 0 ; nn->dephts[1]->f > i ; i++) {
        link(nn->input,nn->dephts[1]->table[i]);
    }
    for(int i = 0 ; nn->dephts[nn->depht]->f > i ; i++) {
        link(nn->dephts[nn->depht]->table[i],nn->end);
    }
    for(int i = 1 ; nn->depht > i ; i++) {
        for(int j = 0 ; nn->dephts[i]->f > j ; j++) {
            for(int k = 0 ; nn->dephts[i+1]->f > k ; k++) {
                link(nn->dephts[i]->table[j],nn->dephts[i+1]->table[k]);
                //printf("Neural (%d,%d) and (%d,%d) successfully linked\n",i,j,i+1,k);
            }
        }
    }
    return 1;
}

float activate_all(n_n* nn, float input) {
    nn->input->input = input;
    activate(nn->input);
    for(int i = 1 ; nn->depht+1 > i ; i++) {
        for(int j = 0 ; nn->dephts[i]->f-1 > j ; j++) {
            activate(nn->dephts[i]->table[j]);
        }
    }
    return nn->end->input;
}

int mutation_n(neural* n) {
    int fact = ((rand()%200) + 1) / 100;
    n->weight *= fact;
    return 1;
}

// int train(n_n* nn, float input, float wanted) {
//     float result = activate_all(nn,input);
//     while(result != wanted) {
//         float result = activate_all(nn,input);
//     }
//     return 1;
// }
