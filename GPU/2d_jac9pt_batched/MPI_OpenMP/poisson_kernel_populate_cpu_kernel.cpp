//
// auto-generated by ops.py
//


// host stub function
#ifndef OPS_LAZY
void ops_par_loop_poisson_kernel_populate(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
const int blockidx_start = 0; const int blockidx_end = block->count;
#ifdef OPS_BATCHED
const int batch_size = block->count;
#endif
#else
void ops_par_loop_poisson_kernel_populate_execute(const char *name, ops_block block, int blockidx_start, int blockidx_end, int dim, int *range, int nargs, ops_arg* args) {
  #ifdef OPS_BATCHED
  const int batch_size = OPS_BATCH_SIZE;
  #endif
  ops_arg arg0 = args[0];
  ops_arg arg1 = args[1];
  ops_arg arg2 = args[2];
  ops_arg arg3 = args[3];
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  #ifndef OPS_LAZY
  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  #endif

  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,4,range,0)) return;
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(0,"poisson_kernel_populate");
    OPS_instance::getOPSInstance()->OPS_kernels[0].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "poisson_kernel_populate");
  #endif


  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  int arg_idx[2];
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 4,block, range, start, end, arg_idx) < 0) return;
  #endif

  #ifdef OPS_MPI
  sub_dat_list sd = OPS_sub_dat_list[args[3].dat->index];
  arg_idx[0] = MAX(0,sd->decomp_disp[0]);
  arg_idx[1] = MAX(0,sd->decomp_disp[1]);
  #else //OPS_MPI
  arg_idx[0] = 0;
  arg_idx[1] = 0;
  #endif //OPS_MPI

  //initialize variable with the dimension of dats
  #if defined(OPS_BATCHED) && OPS_BATCHED==0 && defined(OPS_HYBRID_LAYOUT)
  const int xdim1 = OPS_BATCH_SIZE;
  const int xdim2 = OPS_BATCH_SIZE;
  const int xdim3 = OPS_BATCH_SIZE;
  #else
  const int xdim1 = args[1].dat->size[0];
  const int xdim2 = args[2].dat->size[0];
  const int xdim3 = args[3].dat->size[0];
  #endif
  const int ydim1 = args[1].dat->size[1];
  const int ydim2 = args[2].dat->size[1];
  const int ydim3 = args[3].dat->size[1];
  #ifdef OPS_BATCHED
  const int bounds_0_l = OPS_BATCHED == 0 ? 0 : start[(OPS_BATCHED>0)+-1];
  const int bounds_0_u = OPS_BATCHED == 0 ? MIN(batch_size,block->count-blockidx_start) : end[(OPS_BATCHED>0)+-1];
  const int bounds_1_l = OPS_BATCHED == 1 ? 0 : start[(OPS_BATCHED>1)+0];
  const int bounds_1_u = OPS_BATCHED == 1 ? MIN(batch_size,block->count-blockidx_start) : end[(OPS_BATCHED>1)+0];
  const int bounds_2_l = OPS_BATCHED == 2 ? 0 : start[(OPS_BATCHED>2)+1];
  const int bounds_2_u = OPS_BATCHED == 2 ? MIN(batch_size,block->count-blockidx_start) : end[(OPS_BATCHED>2)+1];
  #else
  const int bounds_0_l = start[0];
  const int bounds_0_u = end[0];
  const int bounds_1_l = start[1];
  const int bounds_1_u = end[1];
  const int bounds_2_l = 0;
  const int bounds_2_u = blockidx_end-blockidx_start;
  #endif

  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 4);
  ops_halo_exchanges(args,4,range);
  ops_H_D_exchanges_host(args, 4);
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_instance::getOPSInstance()->OPS_kernels[0].mpi_time += __t1-__t2;
  }

  //set up initial pointers

  float * __restrict__ u_p = (float *)(args[1].data + args[1].dat->base_offset + blockidx_start * args[1].dat->batch_offset);

  float * __restrict__ f_p = (float *)(args[2].data + args[2].dat->base_offset + blockidx_start * args[2].dat->batch_offset);

  float * __restrict__ ref_p = (float *)(args[3].data + args[3].dat->base_offset + blockidx_start * args[3].dat->batch_offset);


  #if defined(_OPENMP) && defined(OPS_BATCHED) && !defined(OPS_LAZY)
  #pragma omp parallel for
  #endif
  for ( int n_2=bounds_2_l; n_2<bounds_2_u; n_2++ ){
    #if defined(_OPENMP) && !defined(OPS_BATCHED)
    #pragma omp parallel for
    #endif
    for ( int n_1=bounds_1_l; n_1<bounds_1_u; n_1++ ){
      #ifdef __INTEL_COMPILER
      #pragma loop_count(10000)
      #pragma omp simd
      #elif defined(__clang__)
      #pragma clang loop vectorize(assume_safety)
      #elif defined(__GNUC__)
      #pragma simd
      #pragma GCC ivdep
      #else
      #pragma simd
      #endif
      for ( int n_0=bounds_0_l; n_0<bounds_0_u; n_0++ ){
        #if defined(OPS_BATCHED) && OPS_BATCHED==0
        int idx[] = {arg_idx[0]+n_1, arg_idx[1]+n_2, blockidx_start + n_0};
        #elif OPS_BATCHED==1
        int idx[] = {arg_idx[0]+n_0, arg_idx[1]+n_2, blockidx_start + n_1};
        #else
        int idx[] = {arg_idx[0]+n_0, arg_idx[1]+n_1, blockidx_start + n_2};
        #endif
        ACC<float> u(xdim1, ydim1, u_p + n_0 + n_1 * xdim1 + n_2 * xdim1 * ydim1);
        ACC<float> f(xdim2, ydim2, f_p + n_0 + n_1 * xdim2 + n_2 * xdim2 * ydim2);
        ACC<float> ref(xdim3, ydim3, ref_p + n_0 + n_1 * xdim3 + n_2 * xdim3 * ydim3);
        
  float x = dx * (float)(idx[0]);
  float y = dy * (float)(idx[1]);

  u(0,0) = myfun(sin(M_PI*x),cos(2.0f*M_PI*y))-1.0f;
  f(0,0) = -5.0f*M_PI*M_PI*sin(M_PI*x)*cos(2.0f*M_PI*y);
  ref(0,0) = sin(M_PI*x)*cos(2.0f*M_PI*y);

      }
    }
    #if OPS_BATCHED==2 || !defined(OPS_BATCHED)
    #endif
  }
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    OPS_instance::getOPSInstance()->OPS_kernels[0].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 4);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_instance::getOPSInstance()->OPS_kernels[0].mpi_time += __t1-__t2;
    OPS_instance::getOPSInstance()->OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_instance::getOPSInstance()->OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_instance::getOPSInstance()->OPS_kernels[0].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}


#ifdef OPS_LAZY
void ops_par_loop_poisson_kernel_populate(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 0;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 0;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->function = ops_par_loop_poisson_kernel_populate_execute;
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(0,"poisson_kernel_populate");
  }
  ops_enqueue_kernel(desc);
}
#endif
