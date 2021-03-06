//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_poisson_kernel_stencil;
int xdim1_poisson_kernel_stencil;

//user function
#pragma acc routine
inline 
void poisson_kernel_stencil(const ptr_float u,
  ptr_float u2) {
  OPS_ACC(u2, 0,0) = OPS_ACC(u, -1,1)*(-0.07f) + OPS_ACC(u, 0,1) * (-0.06f) + OPS_ACC(u, 1,1)*(-0.05f) \
	    + OPS_ACC(u, -1,0)*(-0.08f) + OPS_ACC(u, 0,0)*0.36f + OPS_ACC(u, 1,0)*(-0.04f) + \
	    OPS_ACC(u, -1,-1)*(-0.01f) + OPS_ACC(u, 0,-1)*(-0.02f) + OPS_ACC(u, 1,-1)*(-0.03f);
}


void poisson_kernel_stencil_c_wrapper(
  float *p_a0,
  float *p_a1,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_float ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_poisson_kernel_stencil*1*1, xdim0_poisson_kernel_stencil};
      ptr_float ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_poisson_kernel_stencil*1*1, xdim1_poisson_kernel_stencil};
      poisson_kernel_stencil( ptr0,
          ptr1 );

    }
  }
}
