#include <bits/stdc++.h>
#include "mandelbro.hpp"
#define MAX 8000
#define H 6000
#define W 10500

using namespace std;

RGB tester[MAXPAL];

RGB mat[H][W];

RGB interpolation(RGB c1, RGB c2, double a){
  RGB temp;
  temp.r = (1-a)*c1.r + a*c2.r;
  temp.g = (1-a)*c1.g + a*c2.g;
  temp.b = (1-a)*c1.b + a*c2.b;
  return temp;
}

int main(){

  int q = 0;
  for(int i = 0; i < 256; i++)
    for(int j = 0; j < 256; j++)
      for(int k = 0; k < 256; k++)
  	tester[q++] = RGB(i,j,k);
  
  double XB = -2.5;
  double YB = -1.0;
  double HL = 2.0;
  double WL = 3.5;
  
  for(int py = 0; py < H; py++){
    for(int px = 0; px < W; px++){
      double x0 = XB + (px/(1.0*W))*WL;
      double y0 = YB + (py/(1.0*H))*HL;

      double x = 0;
      double y = 0;      

      int i;
      double temp;
      for(i = 0; i < MAX && x*x +y*y < (1<<2); i++){
	double xt = x*x - y*y + x0;
	y = 2*x*y + y0;
	x = xt;
      }      

      if(i < MAX){
	double log_zn = log(x*x+y*y)/2.0;
	double nu = log(log_zn/log(2.0))/log(2.0);
	temp = 1.0*i + 1.0 - nu;
      }
      
      // RGB c1 = pallete[((int)floor(temp))%MAXPAL];
      // RGB c2 = pallete[((int)floor(temp)+1)%MAXPAL];

      RGB c1 = tester[((int)floor(temp))%MAXPAL];
      RGB c2 = tester[((int)floor(temp)+1)%MAXPAL];

      double  intpart;
      mat[py][px] = interpolation(c1, c2, modf(temp, &intpart));
      // mat[py][px] = tester[i];
    }
  }

  ofstream out("out.ppm");
  out << "P3" << endl;
  out << "# feep.ppm" << endl;
  out << W << " " << H << endl;
  out << "256" << endl;
  for(int i = 0; i < H; i++){
    for(int j = 0; j < W; j++){
      out << mat[i][j].r << " " << mat[i][j].g << " " << mat[i][j].b << " \n"[j == W-1];
      // out << (255*i)/N << " " << (255*j)/N << " " << "0" << " \n"[j == N-1];

    }
  }
  
  return 0;
}
