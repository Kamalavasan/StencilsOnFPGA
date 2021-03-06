//
// auto-generated by ops.py
//

int xdim0_poisson_kernel_error;
int ydim0_poisson_kernel_error;
int xdim1_poisson_kernel_error;
int ydim1_poisson_kernel_error;


//user function



void poisson_kernel_error_c_wrapper(
  float * restrict u_p,
  float * restrict ref_p,
  float * restrict err_g,
  int x_size, int y_size, int z_size) {
  float err_0 = err_g[0];
  #pragma omp parallel for reduction(+:err_0)
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        float err[1];
        err[0] = ZERO_float;
        const ptr_float u = { u_p + n_x*1 + n_y * xdim0_poisson_kernel_error*1 + n_z * xdim0_poisson_kernel_error * ydim0_poisson_kernel_error*1, xdim0_poisson_kernel_error, ydim0_poisson_kernel_error};
        const ptr_float ref = { ref_p + n_x*1 + n_y * xdim1_poisson_kernel_error*1 + n_z * xdim1_poisson_kernel_error * ydim1_poisson_kernel_error*1, xdim1_poisson_kernel_error, ydim1_poisson_kernel_error};
        
  *err = *err + (OPS_ACC(u, 0,0,0)-OPS_ACC(ref, 0,0,0))*(OPS_ACC(u, 0,0,0)-OPS_ACC(ref, 0,0,0));

        err_0 +=err[0];
      }
    }
  }
  err_g[0] = err_0;
}
