#include <stdio.h>
#include <stdlib.h>
#include "dyn-tables.c"
#include "neurals.c"

int exemple1 () { //Implementation of a neural network in wich we can add neurals with a selected depht
    int depht = 5; //Define the neural network's depht
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

int exemple2() { //Implementation of non-typed dynamic tables
    n_dt* tb = new_ndt();
    neural* n1 = new_neural();
    neural* n2 = new_neural();
    neural* n3 = new_neural();
    add_ndt(tb, n1);
    add_ndt(tb, n2);
    add_ndt(tb, n3);
    printf("Element 1 : %p\n",tb->table[0]);
    printf("Element 2 : %p\n",tb->table[1]);
    delete_ndt(tb);
    delete_neural(n1);
    delete_neural(n2);
    delete_neural(n3);
    return 1;
}

int exemple3() { //Implementation of the exemple1 neural network in wich we can create or remove links
    int depht = 5; //Define the neural network's depht
    n_n* nn = new_n_n(depht);
    for(int i = 1 ; depht+1 > i ; i++) {
        for(int j = 0 ; 10 > j ; j++) {
            add_neural(i,nn);
        }
    }
    printf("Number of neurals in the nn : %d\n\n",nn->elements->filling);
    show_state(nn);
    explore_ndt(nn->dephts[1]->table[2]->output);
    for(int i = 1 ; depht-1 > i ; i++) {
        for(int j = 0 ; 12 > j ; j++) {
            for(int k = 0 ; 12 > k ; k++) {
                link(nn->dephts[i]->table[j],nn->dephts[i+1]->table[k]);
                //printf("Neural (%d,%d) and (%d,%d) successfully linked\n",i,j,i+1,k);
            }
        }
    }
    link(nn->dephts[1]->table[2],nn->dephts[2]->table[2]);
    explore_ndt(nn->dephts[1]->table[2]->output);
    end_program(nn);
    return 1;

}

int exemple4() { //Test of a basic neural network to predict datas with a proportionality relation
    int datas[2000];
    for(int i = 0 ; 2000 > i ; i+=2) {
        datas[i] = rand() % 100;
        datas[i+1] = 1.7 * datas[i];
    }
    // for(int i = 0 ; 2000 > i ; i+=2) {
    //     printf("(%d,%d)\n",datas[i],datas[i+1]);
    // }
    n_n* nn = new_n_n(3);
    link_all(nn);
    for(int i = 0 ; 2000 > i ; i+=2) {
        // datas[i]
    }
    end_program(nn);
    // printf("%d\n",rand());
    return 1;
}

int main() {
    printf("Beginning of program:\n\n");
    n_n* nn = new_n_n(10);
    link_all(nn);
    // show_state(nn);
    // printf("%d\n",nn->end->output->filling);
    // for(int i = 0 ; nn->dephts[nn->depht]->f > i ; i++) {
    //     printf("%p\n",nn->dephts[nn->depht]->table[i]->output->table[0]);
    // }
    // // printf("%p\n",nn->input->output->table[1]);
    printf("%f\n",activate_all(nn,40.0));
    // printf("%f\n",nn->dephts[1]->table[0]->input);
    // nn->input->input = 4.0;
    // activate(nn->input);
    // printf("%f\n",nn->dephts[1]->table[0]->input);
    // printf("%f\n",nn->dephts[2]->table[0]->input);
    // activate(nn->dephts[1]->table[0]);
    // activate(nn->dephts[1]->table[1]);
    // printf("%f\n",nn->dephts[1]->table[0]->input);
    // printf("%f\n",nn->dephts[2]->table[0]->input);
    end_program(nn);
    //exemple4();
    return 1;
}

/*
1) Maintien d'un registre de tous les neurones dans la structure de nn

2) Ajout d'une structure de tabeau dynamique


*/
