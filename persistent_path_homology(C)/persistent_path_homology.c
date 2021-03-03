#include <stdio.h>
#include <stdlib.h>
#include "persistent_path_homology.h"

void generating_all_regular_paths_dim_p (collection_of_basis *B,
                                         unsigned int dim_p,
                                         unsigned int network_set_size){

    base *B_dim_p           = (B -> basis) + dim_p;
    base *B_dim_p_minus_one = (B -> basis) + (dim_p - 1);

    regular_path temp_dim_p, temp_dim_p_minus_one;

    unsigned int i, j, k, l;


    B_dim_p -> dimension_of_the_regular_path                 = dim_p;
    B_dim_p -> dimension_of_the_vector_space_spanned_by_base =  (B_dim_p_minus_one -> dimension_of_the_vector_space_spanned_by_base) *
        (network_set_size - 1);

    (B_dim_p -> base_matrix) = malloc ( (B_dim_p -> dimension_of_the_vector_space_spanned_by_base) * sizeof (regular_path) );

    l = 0;
    for (i = 0; i < B_dim_p_minus_one -> dimension_of_the_vector_space_spanned_by_base; ++i) {

        temp_dim_p_minus_one = (B_dim_p_minus_one -> base_matrix) [i];

        for (j = 0; j < network_set_size; ++j) {
            temp_dim_p = malloc( (dim_p + 1) * sizeof(vertex_index) );

            if ( temp_dim_p_minus_one [dim_p - 1] != j ) {
                for (k = 0; k <= dim_p - 1; ++k) temp_dim_p[k] = temp_dim_p_minus_one[k];
                temp_dim_p[k] = j;
                (B_dim_p -> base_matrix) [l] = temp_dim_p;
                ++l;
            }
        }
    }
}

void Basis_of_the_vector_spaces_spanned_by_regular_paths (collection_of_basis *B,
                                                          unsigned int pph_dim,
                                                          unsigned int network_set_size) {

    unsigned int i;

    B -> basis        = malloc( (pph_dim + 2) * sizeof(base) );
    B -> max_of_basis = pph_dim + 1;

    (B -> basis) -> base_matrix                                   = malloc ( network_set_size * sizeof (regular_path) );
    (B -> basis) -> dimension_of_the_regular_path                 = 0;
    (B -> basis) -> dimension_of_the_vector_space_spanned_by_base = network_set_size;


    for (i = 0; i < network_set_size; ++i) {

        ((B -> basis) -> base_matrix)[i]    = malloc ( sizeof (vertex_index) );
        ((B -> basis) -> base_matrix)[i][0] = i;

    }

    for (i = 1; i <= pph_dim + 1; ++i) {
        generating_all_regular_paths_dim_p (B, i, network_set_size);
    }
}