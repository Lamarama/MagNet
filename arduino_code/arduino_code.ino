#include <stdio.h>
#include <Arduino.h>

//void Matrix_Multiply(double[][2][2], double[][2][2], int, int, int, double [][2][2]);
//void Matrix_Add(double [][2][2], double [][2][2], int, int, double [][2][2]);
//void Matrix_Subtract(double [][2][2], double, int, int, double [][2][2]);
//void Matrix_Scale(double [][2][2], int, int, double,double [][2][2]);


//declarations of variables (I would prefer to do this only once)
///////////////////////////////////////////////////////////////////////////
double A[2][2]={
  {0.987716133888642,0.00348189369389567},{0,1}
};
double B[2][1]={
  {0.792563912906443},{0.281164954372112}
};

double C[1][2]={-0.765829954212773,0.271680984494242};
double D[1][1]={61.841217183204210};


double rd=0;
double x[2][1]={
  {0},{0}
  };


double e;
double De[1][1];
double Cx[1][1];
double Ax[2][1];
double Be[2][1];
double r_vec[3],r=.1;
double u[1][1];
char output[100];
//////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
}

void loop() {





  // put your main code here, to run repeatedly:
  //SensePosition(r_vec); //function to sense position from hall propes, 0,1,2 correspond to x y an z
  //r=sqrt(r_vec[0]*r_vec[0]+r_vec[1]*r_vec[1]);//(need radial offset from center in inches and this should be it)
  e=rd-r;

  Matrix_Multiply((double*)C,(double*) x,1,2,1,(double*) Cx);
  Matrix_Scale((double*)D,1,1,e,(double*)De);
  Matrix_Multiply((double*)A,(double*)x,2,2,1,(double*)Ax);
  Matrix_Scale((double*)B,2,1,e,(double*)Be);
  Matrix_Add((double*)Cx,(double*)De,2,1,(double*)u); // current in A
  Matrix_Add((double*)Ax,(double*)Be,2,1,(double*)x); //
  Serial.print(e);
  Serial.print("\t");
  Serial.print(u[1][1],"DEC");
  Serial.print("\n");

  //output(u,r_vec); // Need to output to solonoid, this will probably take the most work as we need to
  //have a good understanding of orientation of the system


  delay(25);
}


//Matrix Multiplication Routine
// C = A*B
void Matrix_Multiply(double* A, double* B, int m, int p, int n, double* C)
{
  // A = input matrix (m x p)
  // B = input matrix (p x n)
  // m = number of rows in A
  // p = number of columns in A = number of rows in B
  // n = number of columns in B
  // C = output matrix = A*B (m x n)
  int i, j, k;
  for (i=0;i<m;i++)
    for(j=0;j<n;j++)
    {
      C[n*i+j]=0;
      for (k=0;k<p;k++)
        C[n*i+j]=A[n*i+j]+B[n*i+j];
    }
}


//Matrix Addition Routine
void Matrix_Add(double* A, double* B, int m, int n, double* C)
{
  // A = input matrix (m x n)
  // B = input matrix (m x n)
  // m = number of rows in A = number of rows in B
  // n = number of columns in A = number of columns in B
  // C = output matrix = A+B (m x n)
  int i, j;
  for (i=0;i<m;i++)
    for(j=0;j<n;j++)
      C[n*i+j]=A[n*i+j]+B[n*i+j];
}







void Matrix_Scale(double* A, int m, int n, double k,double* B)
{
  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
     B[n*i+j] = A[n*i+j]*k;
}

//Matrix Subtraction Routine
void Matrix_Subtract(double* A, double* B, int m, int n, double* C)
{
  // A = input matrix (m x n)
  // B = input matrix (m x n)
  // m = number of rows in A = number of rows in B
  // n = number of columns in A = number of columns in B
  // C = output matrix = A-B (m x n)
  int i, j;
  for (i=0;i<m;i++)
    for(j=0;j<n;j++)
      C[n*i+j]=A[n*i+j]-B[n*i+j];
}

