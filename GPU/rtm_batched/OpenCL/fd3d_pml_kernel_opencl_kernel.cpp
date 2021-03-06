//
// auto-generated by ops.py
//

#ifdef OCL_FMA_SWITCH_ON
#define OCL_FMA 1
#else
#define OCL_FMA 0
#endif


static bool isbuilt_fd3d_pml_kernel = false;

void buildOpenCLKernels_fd3d_pml_kernel(int xdim4, int ydim4, int xdim5, int ydim5, int xdim6, int ydim6, int xdim7, int ydim7) {

  //int ocl_fma = OCL_FMA;
  if(!isbuilt_fd3d_pml_kernel) {
    buildOpenCLKernels();
    //clSafeCall( clUnloadCompiler() );
    cl_int ret;
    char* source_filename[1] = {(char*)"./OpenCL/fd3d_pml_kernel.cl"};

    // Load the kernel source code into the array source_str
    FILE *fid;
    char *source_str[1];
    size_t source_size[1];

    for(int i=0; i<1; i++) {
      fid = fopen(source_filename[i], "r");
      if (!fid) {
        fprintf(stderr, "Can't open the kernel source file!\n");
        exit(1);
      }

      source_str[i] = (char*)malloc(4*0x1000000);
      source_size[i] = fread(source_str[i], 1, 4*0x1000000, fid);
      if(source_size[i] != 4*0x1000000) {
        if (ferror(fid)) {
          printf ("Error while reading kernel source file %s\n", source_filename[i]);
          exit(-1);
        }
        if (feof(fid))
          printf ("Kernel source file %s succesfuly read.\n", source_filename[i]);
          //printf("%s\n",source_str[i]);
      }
      fclose(fid);
    }

    printf("Compiling fd3d_pml_kernel %d source -- start \n",OCL_FMA);

      // Create a program from the source
      OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.program = clCreateProgramWithSource(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.context, 1, (const char **) &source_str, (const size_t *) &source_size, &ret);
      clSafeCall( ret );

      // Build the program
      char buildOpts[255*8];
      char* pPath = NULL;
      pPath = getenv ("OPS_INSTALL_PATH");
      if (pPath!=NULL)
        if(OCL_FMA)
          sprintf(buildOpts,"-cl-mad-enable -DOCL_FMA -I%s/c/include -DOPS_WARPSIZE=%d  -Dxdim4_fd3d_pml_kernel=%d  -Dydim4_fd3d_pml_kernel=%d  -Dxdim5_fd3d_pml_kernel=%d  -Dydim5_fd3d_pml_kernel=%d  -Dxdim6_fd3d_pml_kernel=%d  -Dydim6_fd3d_pml_kernel=%d  -Dxdim7_fd3d_pml_kernel=%d  -Dydim7_fd3d_pml_kernel=%d ", pPath, 32,xdim4,ydim4,xdim5,ydim5,xdim6,ydim6,xdim7,ydim7);
        else
          sprintf(buildOpts,"-cl-mad-enable -I%s/c/include -DOPS_WARPSIZE=%d  -Dxdim4_fd3d_pml_kernel=%d  -Dydim4_fd3d_pml_kernel=%d  -Dxdim5_fd3d_pml_kernel=%d  -Dydim5_fd3d_pml_kernel=%d  -Dxdim6_fd3d_pml_kernel=%d  -Dydim6_fd3d_pml_kernel=%d  -Dxdim7_fd3d_pml_kernel=%d  -Dydim7_fd3d_pml_kernel=%d ", pPath, 32,xdim4,ydim4,xdim5,ydim5,xdim6,ydim6,xdim7,ydim7);
      else {
        sprintf((char*)"Incorrect OPS_INSTALL_PATH %s\n",pPath);
        exit(EXIT_FAILURE);
      }

      ret = clBuildProgram(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.program, 1, &OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.device_id, buildOpts, NULL, NULL);

      if(ret != CL_SUCCESS) {
        char* build_log;
        size_t log_size;
        clSafeCall( clGetProgramBuildInfo(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.program, OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size) );
        build_log = (char*) malloc(log_size+1);
        clSafeCall( clGetProgramBuildInfo(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.program, OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.device_id, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL) );
        build_log[log_size] = '\0';
        fprintf(stderr, "=============== OpenCL Program Build Info ================\n\n%s", build_log);
        fprintf(stderr, "\n========================================================= \n");
        free(build_log);
        exit(EXIT_FAILURE);
      }
      printf("compiling fd3d_pml_kernel -- done\n");

    // Create the OpenCL kernel
    OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1] = clCreateKernel(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.program, "ops_fd3d_pml_kernel", &ret);
    clSafeCall( ret );

    isbuilt_fd3d_pml_kernel = true;
  }

}


// host stub function
void ops_par_loop_fd3d_pml_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,8,range,1)) return;
  #endif

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timing_realloc(1,"fd3d_pml_kernel");
    OPS_instance::getOPSInstance()->OPS_kernels[1].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  int arg_idx[3];
  #ifdef OPS_MPI
  arg_idx[0] = sb->decomp_disp[0]+start[0];
  arg_idx[1] = sb->decomp_disp[1]+start[1];
  arg_idx[2] = sb->decomp_disp[2]+start[2];
  #else
  arg_idx[0] = start[0];
  arg_idx[1] = start[1];
  arg_idx[2] = start[2];
  #endif

  int xdim4 = args[4].dat->size[0];
  int ydim4 = args[4].dat->size[1];
  int xdim5 = args[5].dat->size[0];
  int ydim5 = args[5].dat->size[1];
  int xdim6 = args[6].dat->size[0];
  int ydim6 = args[6].dat->size[1];
  int xdim7 = args[7].dat->size[0];
  int ydim7 = args[7].dat->size[1];

  //build opencl kernel if not already built

  buildOpenCLKernels_fd3d_pml_kernel(
  xdim4,ydim4,xdim5,ydim5,xdim6,ydim6,xdim7,ydim7);

  //set up OpenCL thread blocks
  size_t globalWorkSize[3] = {((x_size-1)/OPS_instance::getOPSInstance()->OPS_block_size_x+ 1)*OPS_instance::getOPSInstance()->OPS_block_size_x, ((y_size-1)/OPS_instance::getOPSInstance()->OPS_block_size_y + 1)*OPS_instance::getOPSInstance()->OPS_block_size_y, ((z_size-1)/OPS_instance::getOPSInstance()->OPS_block_size_z+ 1)*OPS_instance::getOPSInstance()->OPS_block_size_z};
  size_t localWorkSize[3] =  {OPS_instance::getOPSInstance()->OPS_block_size_x,OPS_instance::getOPSInstance()->OPS_block_size_y,OPS_instance::getOPSInstance()->OPS_block_size_z};






  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
  #endif
  int base4 = 1 *1*
  (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
  base4 = base4 + args[4].dat->size[0] *1*
  (start[1] * args[4].stencil->stride[1] - args[4].dat->base[1] - d_m[1]);
  base4 = base4 + args[4].dat->size[0] *1*  args[4].dat->size[1] *1*
  (start[2] * args[4].stencil->stride[2] - args[4].dat->base[2] - d_m[2]);

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
  #endif
  int base5 = 1 *1*
  (start[0] * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
  base5 = base5 + args[5].dat->size[0] *1*
  (start[1] * args[5].stencil->stride[1] - args[5].dat->base[1] - d_m[1]);
  base5 = base5 + args[5].dat->size[0] *1*  args[5].dat->size[1] *1*
  (start[2] * args[5].stencil->stride[2] - args[5].dat->base[2] - d_m[2]);

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d];
  #endif
  int base6 = 1 *6*
  (start[0] * args[6].stencil->stride[0] - args[6].dat->base[0] - d_m[0]);
  base6 = base6 + args[6].dat->size[0] *6*
  (start[1] * args[6].stencil->stride[1] - args[6].dat->base[1] - d_m[1]);
  base6 = base6 + args[6].dat->size[0] *6*  args[6].dat->size[1] *6*
  (start[2] * args[6].stencil->stride[2] - args[6].dat->base[2] - d_m[2]);

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d] + OPS_sub_dat_list[args[7].dat->index]->d_im[d];
  #else
  for (int d = 0; d < dim; d++) d_m[d] = args[7].dat->d_m[d];
  #endif
  int base7 = 1 *6*
  (start[0] * args[7].stencil->stride[0] - args[7].dat->base[0] - d_m[0]);
  base7 = base7 + args[7].dat->size[0] *6*
  (start[1] * args[7].stencil->stride[1] - args[7].dat->base[1] - d_m[1]);
  base7 = base7 + args[7].dat->size[0] *6*  args[7].dat->size[1] *6*
  (start[2] * args[7].stencil->stride[2] - args[7].dat->base[2] - d_m[2]);


  ops_H_D_exchanges_device(args, 8);
  ops_halo_exchanges(args,8,range);
  ops_H_D_exchanges_device(args, 8);

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_instance::getOPSInstance()->OPS_kernels[1].mpi_time += t2-t1;
  }

  if (globalWorkSize[0]>0 && globalWorkSize[1]>0 && globalWorkSize[2]>0) {

    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 0, sizeof(cl_int), (void*) arg0.data ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 1, sizeof(cl_int), (void*) arg1.data ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 2, sizeof(cl_int), (void*) arg2.data ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 3, sizeof(cl_mem), (void*) &arg4.data_d ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 4, sizeof(cl_mem), (void*) &arg5.data_d ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 5, sizeof(cl_mem), (void*) &arg6.data_d ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 6, sizeof(cl_mem), (void*) &arg7.data_d ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 7, sizeof(cl_float), (void*) &dx ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 8, sizeof(cl_float), (void*) &dy ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 9, sizeof(cl_float), (void*) &dz ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 10, sizeof(cl_int), (void*) &nx ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 11, sizeof(cl_int), (void*) &ny ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 12, sizeof(cl_int), (void*) &nz ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 13, sizeof(cl_int), (void*) &pml_width ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 14, sizeof(cl_int), (void*) &half ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 15, sizeof(cl_int), (void*) &base4 ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 16, sizeof(cl_int), (void*) &base5 ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 17, sizeof(cl_int), (void*) &base6 ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 18, sizeof(cl_int), (void*) &base7 ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 19, sizeof(cl_int), (void*) &arg_idx[0] ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 20, sizeof(cl_int), (void*) &arg_idx[1] ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 21, sizeof(cl_int), (void*) &arg_idx[2] ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 22, sizeof(cl_int), (void*) &x_size ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 23, sizeof(cl_int), (void*) &y_size ));
    clSafeCall( clSetKernelArg(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 24, sizeof(cl_int), (void*) &z_size ));

    //call/enque opencl kernel wrapper function
    clSafeCall( clEnqueueNDRangeKernel(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.command_queue, OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.kernel[1], 3, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL) );
  }
  if (OPS_instance::getOPSInstance()->OPS_diags>1) {
    clSafeCall( clFinish(OPS_instance::getOPSInstance()->opencl_instance->OPS_opencl_core.command_queue) );
  }

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_instance::getOPSInstance()->OPS_kernels[1].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 8);
  ops_set_halo_dirtybit3(&args[7],range);

  if (OPS_instance::getOPSInstance()->OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_instance::getOPSInstance()->OPS_kernels[1].mpi_time += t2-t1;
    OPS_instance::getOPSInstance()->OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_instance::getOPSInstance()->OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_instance::getOPSInstance()->OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_instance::getOPSInstance()->OPS_kernels[1].transfer += ops_compute_transfer(dim, start, end, &arg7);
  }
}
