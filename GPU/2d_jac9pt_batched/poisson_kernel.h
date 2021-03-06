#ifndef poisson_KERNEL_H
#define poisson_KERNEL_H

void poisson_kernel_populate(const int *idx, ACC<float> &u, ACC<float> &f, ACC<float> &ref) {
  float x = dx * (float)(idx[0]);
  float y = dy * (float)(idx[1]);

  u(0,0) = myfun(sin(M_PI*x),cos(2.0f*M_PI*y))-1.0f;
  f(0,0) = -5.0f*M_PI*M_PI*sin(M_PI*x)*cos(2.0f*M_PI*y);
  ref(0,0) = sin(M_PI*x)*cos(2.0f*M_PI*y);
}

void poisson_kernel_initialguess(ACC<float> &u) {
  u(0,0) = 0.0;
}

void poisson_kernel_stencil(const ACC<float> &u, ACC<float> &u2) {
  u2(0,0) = u(-1,1)*(-0.07f) + u(0,1) * (-0.06f) + u(1,1)*(-0.05f) \
	    + u(-1,0)*(-0.08f) + u(0,0)*0.36f + u(1,0)*(-0.04f) + \
	    u(-1,-1)*(-0.01f) + u(0,-1)*(-0.02f) + u(1,-1)*(-0.03f);
}

void poisson_kernel_update(const ACC<float> &u2, ACC<float> &u) {
  u(0,0) = u2(0,0);
}

void poisson_kernel_error(const ACC<float> &u, const ACC<float> &ref, float *err) {
  *err = *err + (u(0,0)-ref(0,0))*(u(0,0)-ref(0,0));
}

#endif //poisson_KERNEL_H
