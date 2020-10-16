//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#define OPS_3D
#define OPS_API 2
#define OPS_NO_GLOBALS
#include "ops_macros.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

//user function

void fd3d_pml_kernel(const int *dispx,
  const int *dispy,
  const int *dispz,
  const int *idx,
  const ptr_float rho,
  const ptr_float mu,
  const ptrm_float  yy,
  ptrm_float  dyy, const float dx, const float dy, const float dz, const int nx, const int ny, const int nz, const int pml_width, const int half)
{


  const float c[9] = {0.0035714285714285713,-0.0380952380952381,0.2,-0.8,0.0,0.8,-0.2,0.0380952380952381,-0.0035714285714285713};
  float invdx = 1.0 / dx;
  float invdy = 1.0 / dy;
  float invdz = 1.0 / dz;
  int xbeg=half;
  int xend=nx-half;
  int ybeg=half;
  int yend=ny-half;
  int zbeg=half;
  int zend=nz-half;
  int xpmlbeg=xbeg+pml_width;
  int ypmlbeg=ybeg+pml_width;
  int zpmlbeg=zbeg+pml_width;
  int xpmlend=xend-pml_width;
  int ypmlend=yend-pml_width;
  int zpmlend=zend-pml_width;

  float sigma = OPS_ACCS(mu, 0,0,0)/OPS_ACCS(rho, 0,0,0);
  float sigmax=0.0;
  float sigmay=0.0;
  float sigmaz=0.0;
  if(idx[0]<=xbeg+pml_width){
    sigmax = (xbeg+pml_width-idx[0])*sigma * 0.1f;
  }
  if(idx[0]>=xend-pml_width){
    sigmax=(idx[0]-(xend-pml_width))*sigma * 0.1f;
  }
  if(idx[1]<=ybeg+pml_width){
    sigmay=(ybeg+pml_width-idx[1])*sigma * 0.1f;
  }
  if(idx[1]>=yend-pml_width){
    sigmay=(idx[1]-(yend-pml_width))*sigma * 0.1f;
  }
  if(idx[2]<=zbeg+pml_width){
    sigmaz=(zbeg+pml_width-idx[2])*sigma * 0.1f;
  }
  if(idx[2]>=zend-pml_width){
    sigmaz=(idx[2]-(zend-pml_width))*sigma * 0.1f;
  }



  float px = OPS_ACCM(yy, 0,0,0,0);
  float py = OPS_ACCM(yy, 1,0,0,0);
  float pz = OPS_ACCM(yy, 2,0,0,0);

  float vx = OPS_ACCM(yy, 3,0,0,0);
  float vy = OPS_ACCM(yy, 4,0,0,0);
  float vz = OPS_ACCM(yy, 5,0,0,0);

  float vxx=0.0;
  float vxy=0.0;
  float vxz=0.0;

  float vyx=0.0;
  float vyy=0.0;
  float vyz=0.0;

  float vzx=0.0;
  float vzy=0.0;
  float vzz=0.0;

  float pxx=0.0;
  float pxy=0.0;
  float pxz=0.0;

  float pyx=0.0;
  float pyy=0.0;
  float pyz=0.0;

  float pzx=0.0;
  float pzy=0.0;
  float pzz=0.0;

  for(int i=-half;i<=half;i++){
    pxx += OPS_ACCM(yy, 0,i,0,0)*c[i+half];
    pyx += OPS_ACCM(yy, 1,i,0,0)*c[i+half];
    pzx += OPS_ACCM(yy, 2,i,0,0)*c[i+half];

    vxx += OPS_ACCM(yy, 3,i,0,0)*c[i+half];
    vyx += OPS_ACCM(yy, 4,i,0,0)*c[i+half];
    vzx += OPS_ACCM(yy, 5,i,0,0)*c[i+half];

    pxy += OPS_ACCM(yy, 0,0,i,0)*c[i+half];
    pyy += OPS_ACCM(yy, 1,0,i,0)*c[i+half];
    pzy += OPS_ACCM(yy, 2,0,i,0)*c[i+half];

    vxy += OPS_ACCM(yy, 3,0,i,0)*c[i+half];
    vyy += OPS_ACCM(yy, 4,0,i,0)*c[i+half];
    vzy += OPS_ACCM(yy, 5,0,i,0)*c[i+half];

    pxz += OPS_ACCM(yy, 0,0,0,i)*c[i+half];
    pyz += OPS_ACCM(yy, 1,0,0,i)*c[i+half];
    pzz += OPS_ACCM(yy, 2,0,0,i)*c[i+half];

    vxz += OPS_ACCM(yy, 3,0,0,i)*c[i+half];
    vyz += OPS_ACCM(yy, 4,0,0,i)*c[i+half];
    vzz += OPS_ACCM(yy, 5,0,0,i)*c[i+half];
  }

  pxx *= invdx;
  pyx *= invdx;
  pzx *= invdx;

  vxx *= invdx;
  vyx *= invdx;
  vzx *= invdx;

  pxy *= invdy;
  pyy *= invdy;
  pzy *= invdy;

  vxy *= invdy;
  vyy *= invdy;
  vzy *= invdy;

  pxz *= invdz;
  pyz *= invdz;
  pzz *= invdz;

  vxz *= invdz;
  vyz *= invdz;
  vzz *= invdz;

  OPS_ACCM(dyy, 0,0,0,0)=vxx/OPS_ACCS(rho, 0,0,0) - sigmax*px;
  OPS_ACCM(dyy, 3,0,0,0)=(pxx+pyx+pxz)*OPS_ACCS(mu, 0,0,0) - sigmax*vx;

  OPS_ACCM(dyy, 1,0,0,0)=vyy/OPS_ACCS(rho, 0,0,0) - sigmay*py;
  OPS_ACCM(dyy, 4,0,0,0)=(pxy+pyy+pyz)*OPS_ACCS(mu, 0,0,0) - sigmay*vy;

  OPS_ACCM(dyy, 2,0,0,0)=vzz/OPS_ACCS(rho, 0,0,0) - sigmaz*pz;
  OPS_ACCM(dyy, 5,0,0,0)=(pxz+pyz+pzz)*OPS_ACCS(mu, 0,0,0) - sigmaz*vz;

}


__kernel void ops_fd3d_pml_kernel(
const int arg0,
const int arg1,
const int arg2,
__global const float* restrict arg4,
__global const float* restrict arg5,
__global const float* restrict arg6,
__global float* restrict arg7,
const float dx,
const float dy,
const float dz,
const int nx,
const int ny,
const int nz,
const int pml_width,
const int half,
const int base4,
const int base5,
const int base6,
const int base7,
int arg_idx0, int arg_idx1, int arg_idx2,
const int size0,
const int size1,
const int size2 ){


  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  int arg_idx[3];
  arg_idx[0] = arg_idx0+idx_x;
  arg_idx[1] = arg_idx1+idx_y;
  arg_idx[2] = arg_idx2+idx_z;
  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    const ptr_float ptr4 = { &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_fd3d_pml_kernel + idx_z * 1*1 * xdim4_fd3d_pml_kernel * ydim4_fd3d_pml_kernel], xdim4_fd3d_pml_kernel, ydim4_fd3d_pml_kernel};
    const ptr_float ptr5 = { &arg5[base5 + idx_x * 1*1 + idx_y * 1*1 * xdim5_fd3d_pml_kernel + idx_z * 1*1 * xdim5_fd3d_pml_kernel * ydim5_fd3d_pml_kernel], xdim5_fd3d_pml_kernel, ydim5_fd3d_pml_kernel};
    #ifdef OPS_SOA
    const ptrm_float ptr6 = { &arg6[base6 + idx_x * 1*6 + idx_y * 1*6 * xdim6_fd3d_pml_kernel + idx_z * 1*6 * xdim6_fd3d_pml_kernel * ydim6_fd3d_pml_kernel], xdim6_fd3d_pml_kernel, ydim6_fd3d_pml_kernel, zdim6_fd3d_pml_kernel};
    #else
    const ptrm_float ptr6 = { &arg6[base6 + idx_x * 1*6 + idx_y * 1*6 * xdim6_fd3d_pml_kernel + idx_z * 1*6 * xdim6_fd3d_pml_kernel * ydim6_fd3d_pml_kernel], xdim6_fd3d_pml_kernel, ydim6_fd3d_pml_kernel, 6};
    #endif
    #ifdef OPS_SOA
    ptrm_float ptr7 = { &arg7[base7 + idx_x * 1*6 + idx_y * 1*6 * xdim7_fd3d_pml_kernel + idx_z * 1*6 * xdim7_fd3d_pml_kernel * ydim7_fd3d_pml_kernel], xdim7_fd3d_pml_kernel, ydim7_fd3d_pml_kernel, zdim7_fd3d_pml_kernel};
    #else
    ptrm_float ptr7 = { &arg7[base7 + idx_x * 1*6 + idx_y * 1*6 * xdim7_fd3d_pml_kernel + idx_z * 1*6 * xdim7_fd3d_pml_kernel * ydim7_fd3d_pml_kernel], xdim7_fd3d_pml_kernel, ydim7_fd3d_pml_kernel, 6};
    #endif
    fd3d_pml_kernel(&arg0,
                    &arg1,
                    &arg2,
                    arg_idx,
                    ptr4,
                    ptr5,
                    ptr6,
                    ptr7,
                    dx,
                    dy,
                    dz,
                    nx,
                    ny,
                    nz,
                    pml_width,
                    half);
  }

}