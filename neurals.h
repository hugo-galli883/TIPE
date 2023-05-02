struct neural {
    int id;
    float weight;
    float input;
    n_dt* output;//struct neural** output;
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
    n_dt* elements;
    layer** dephts; //Table containing address to layers
    neural* input;
    neural* end;
};
typedef struct neural_network n_n;

neural *new_neural();
layer* new_layer(int n, n_n* nn);
n_n* new_n_n(int d);
int delete_neural(neural* n);
int add_neural(int d, n_n* nn);
int end_program(n_n* nn);
int show_state(n_n* nn);
int link(neural* n1, neural* n2);
int add_input(neural* n, float x);
int activate(neural* n);
int link_all(n_n* nn);
float activate_all(n_n* nn, float input);
int mutation_n(neural* n);
