//
// auto-generated by ops.py
//


// host stub function
#ifndef OPS_LAZY
void ops_par_loop_poisson_kernel_error(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {
const int blockidx_start = 0; const int blockidx_end = block->count;
#ifdef OPS_BATCHED
const int batch_size = block->count;
#endif
#else
void ops_par_loop_poisson_kernel_error_execute(const char *name, ops_block block, int blockidx_start, int blockidx_end, int dim, int *range, int nargs, ops_arg* args) {
  #ifdef OPS_BATCHED
  const int batch_size = OPS_BATCH_SIZE;
  #endif
  ops_arg arg0 = args[0];
  ops_arg arg1 = args[1];
  ops_arg arg2 = args[2];
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  #ifndef OPS_LAZY
  ops_arg args[3] = { arg0, arg1, arg2};


  #endif

  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,3,range,5)) return;
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(5,"poisson_kernel_error");
    OPS_instance::getOPSInstance()->OPS_kernels[5].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "poisson_kernel_error");
  #endif


  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];
  #ifdef OPS_MPI
  int arg_idx[2];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 3,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize variable with the dimension of dats
  #if defined(OPS_BATCHED) && OPS_BATCHED==0 && defined(OPS_HYBRID_LAYOUT)
  const int xdim0 = OPS_BATCH_SIZE;
  const int xdim1 = OPS_BATCH_SIZE;
  #else
  const int xdim0 = args[0].dat->size[0];
  const int xdim1 = args[1].dat->size[0];
  #endif
  const int ydim0 = args[0].dat->size[1];
  const int ydim1 = args[1].dat->size[1];
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
  ops_H_D_exchanges_host(args, 3);
  ops_halo_exchanges(args,3,range);
  ops_H_D_exchanges_host(args, 3);
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_instance::getOPSInstance()->OPS_kernels[5].mpi_time += __t1-__t2;
  }

  //set up initial pointers
  float * __restrict__ u_p = (float *)(args[0].data + args[0].dat->base_offset + blockidx_start * args[0].dat->batch_offset);

  float * __restrict__ ref_p = (float *)(args[1].data + args[1].dat->base_offset + blockidx_start * args[1].dat->batch_offset);

  #ifdef OPS_MPI
  float * __restrict__ p_a2 = (float *)(((ops_reduction)args[2].data)->data + ((ops_reduction)args[2].data)->size * block->index + ((ops_reduction)args[2].data)->size * blockidx_start);
  #else //OPS_MPI
  float * __restrict__ p_a2 = (float *)(((ops_reduction)args[2].data)->data + ((ops_reduction)args[2].data)->size * blockidx_start);
  #endif //OPS_MPI



  #if defined(_OPENMP) && defined(OPS_BATCHED) && !defined(OPS_LAZY) && OPS_BATCHED==2
  #pragma omp parallel for
  #endif
  for ( int n_2=bounds_2_l; n_2<bounds_2_u; n_2++ ){
    #if OPS_BATCHED==2 || !defined(OPS_BATCHED)
    float p_a2_0 = p_a2[n_2*1+0];
    #endif
    #if defined(_OPENMP) && !defined(OPS_BATCHED)
    #pragma omp parallel for reduction(+:p_a2_0)
    #endif
    for ( int n_1=bounds_1_l; n_1<bounds_1_u; n_1++ ){
      #if OPS_BATCHED==1
      float p_a2_0 = p_a2[n_1*1+0];
      #endif
      #ifdef __INTEL_COMPILER
      #pragma loop_count(10000)
      #if defined(OPS_BATCHED) && OPS_BATCHED==0
      #pragma omp simd
      #else
      #pragma omp simd reduction(+:p_a2_0)
      #endif
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
        float p_a2_0 = p_a2[n_0*1+0];
        #endif
        const ACC<float> u(xdim0, ydim0, u_p + n_0 + n_1 * xdim0 + n_2 * xdim0 * ydim0);
        const ACC<float> ref(xdim1, ydim1, ref_p + n_0 + n_1 * xdim1 + n_2 * xdim1 * ydim1);
        float err[1];
        err[0] = ZERO_float;
        
  *err = *err + (u(0,0)-ref(0,0))*(u(0,0)-ref(0,0));

        p_a2_0 +=err[0];
        #if defined(OPS_BATCHED) && OPS_BATCHED==0
        p_a2[n_0*1+0] = p_a2_0;
        #endif
      }
      #if OPS_BATCHED==1
      p_a2[n_1*1+0] = p_a2_0;
      #endif
    }
    #if OPS_BATCHED==2 || !defined(OPS_BATCHED)
    p_a2[n_2*1+0] = p_a2_0;
    #endif
  }
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    OPS_instance::getOPSInstance()->OPS_kernels[5].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 3);
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_instance::getOPSInstance()->OPS_kernels[5].mpi_time += __t1-__t2;
    OPS_instance::getOPSInstance()->OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_instance::getOPSInstance()->OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}


#ifdef OPS_LAZY
void ops_par_loop_poisson_kernel_error(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 5;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 5;
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 3;
  desc->args = (ops_arg*)malloc(3*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->function = ops_par_loop_poisson_kernel_error_execute;
  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(5,"poisson_kernel_error");
  }
  ops_enqueue_kernel(desc);
}
#endif
