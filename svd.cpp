// $Id: svd.cpp,v 1.1 2008/05/06 02:26:20 samn Exp $ 
#include "stdafx.h"
#include "Lapack.h"
#include "svd.hpp"
#include <iostream>
#include <algorithm>
//using namespace Lapack;
using namespace std;

void svd(Matrix &u_, Vector &w_,Matrix& v_){

  char jobz = 'A';
  u16 dim_=u_.size();

  //TD changes here
  //   long m=u_.nRows();
  //   long n=u_.nColumns();
  long m=u_.size();
  long n=u_[0].size();
  //changes until here

  double *a= new double[m*n];
  long lda=n;
  double *s= new double[n];
  double *u = new double[n*n];
  long ldu=n;
  double *vt = new double[n*n];
  long ldvt=n;
  long lwork = max(14*min(m,n)+4,10*min(m,n)+2+ SMLSIZ*(SMLSIZ+8))+max(m,m);
  double* work= new double[lwork];
  long * iwork=new long[8*min(m,n)];
  long info;


  for(u16 rowIdx = 0; rowIdx < dim_; rowIdx++)
    for(u16 columnIdx = 0; columnIdx < dim_; columnIdx++) {
      a[columnIdx*dim_ + rowIdx] = u_[rowIdx][columnIdx];
    }


  lwork=-1;
  //::std::cout << "lwork=" << lwork << ::std::endl;
  dgesdd( &jobz, &m, &n,  a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, iwork, &info );

  lwork=long(work[0]);
  //::std::cout << "lwork=" << lwork << ::std::endl;
  delete[] work;
  work=new double[lwork];

  dgesdd( &jobz, &m, &n,  a, &lda, s, u, &ldu, vt, &ldvt, work, &lwork, iwork, &info );

  for(u16 rowIdx = 0; rowIdx < dim_; rowIdx++){
    for(u16 columnIdx = 0; columnIdx < dim_; columnIdx++) {
      u_[rowIdx][columnIdx] = u[columnIdx*dim_ + rowIdx];
      v_[rowIdx][columnIdx] = vt[columnIdx*dim_ + rowIdx];
    }
    w_[rowIdx]=s[rowIdx];
  }
  delete[] a;
  delete[] s;
  delete[] u;
  delete[] vt;
  delete[] work;
  delete[] iwork;
}
