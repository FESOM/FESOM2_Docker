
/* Call remap_get_num_weights to get the length of the weigth arrays, then allocate the arrays and hand to remap_get_weights. */

/* Bounds are in degree, the pole is in cartitian coordinates on a unit sphere
   and a pole of (0,0,0) means all great circles (no lon-lat grid). */
extern "C" void remap_get_num_weights(const double* src_bounds_lon, const double* src_bounds_lat, int n_vert_per_cell_src, int n_cell_src,
                     const double* src_pole,
                     const double* dst_bounds_lon, const double* dst_bounds_lat, int n_vert_per_cell_dst, int n_cell_dst,
                     const double* dst_pole,
                     int order, int* n_weights);

/* centre_??? or areas can be a NULL pointer if only one of them is required */
extern "C" void remap_get_barycentres_and_areas(const double* bounds_lon, const double* bounds_lat, int n_vert_per_cell, int n_cell,
                     const double* pole,
                     double* centre_lon, double* centre_lat, double* areas);

/*
extern "C" void remap_get_weights(double* weights, int* src_indices, int* src_ranks, int* dst_indices);
*/
extern "C" void remap_get_weights(double* weights, int* src_indices, int* dst_indices);
