
struct neural_dynamic_table {
    void** table;
    int filling;
    int capacity;
};
typedef struct neural_dynamic_table n_dt;

n_dt* new_ndt();
int add_ndt (n_dt* t, void* n);
int delete_ndt(n_dt* ndt); //Warning : the function deletes the table but not the neurals it points to. Look hard_dlt_ndt
int remove_el_ndt(n_dt* ndt, void* n);
int remove_id_ndt(n_dt* ndt, int n);
// int hard_dlt_ndt(n_dt* ndt);
int explore_ndt(n_dt* ndt);
