//
// auto-generated by ops.py//

//header
#define OPS_3D
#define OPS_API 2
#include "ops_lib_cpp.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

// global constants
extern float dx;
extern float dy;
extern float dz;
extern int nx;
extern int ny;
extern int nz;
extern int pml_width;
extern int half;
extern int order;

void ops_init_backend() {}

//user kernel files
#include "rtm_kernel_populate_cpu_kernel.cpp"
#include "fd3d_pml_kernel_cpu_kernel.cpp"
#include "calc_ytemp_kernel_cpu_kernel.cpp"
#include "calc_ytemp2_kernel_cpu_kernel.cpp"
#include "final_update_kernel_cpu_kernel.cpp"
