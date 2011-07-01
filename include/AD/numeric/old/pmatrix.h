//////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 1994 Allen Leung.  All rights reserved.
//  Email: aleung@netcom.com
//
//  This file is part of the ADLib C++ library.  This library is distributed 
//  in hope that it will be useful, but WITHOUT ANY WARRANTY whatsoever. 
//  This source code is NOT public domain.  Please see the files "copying" 
//  and "copying.al" for the conditions under which ADLib may be distributed, 
//  modified and used.
//////////////////////////////////////////////////////////////////////////////

#ifndef matrix_template_h
#define matrix_template_h

//
// Class AMatrix<Element> is the usual matrix data type
// parametrized by the type of the element.  Thus it is 
// possible to have matrices with elements something other
// than float's or double's---in fact, as long as the
// class Element is a field(in the algebraic sense) 
// this class can be utilized.
//
// For example, we can have AMatrix<Complex>, or AMatrix<Z<n>>,
// or even AMatrix<Matrix<Complex>>.
//

template<class Element>
   class AMatrix {

      int M, N;     // number of rows and columns
      Element * A;  // An array that holds the elements
      Element zero; // zero element
      Element one;  // identity element

   public:
      AMatrix(int rows, int columns);
      AMatrix(int rows, int columns, const Element&);
      AMatrix(const AMatrix&);
     ~AMatrix() { delete [] A; }
      friend AMatrix I(int row, int column, 
                      const Element& zero, const Element& one);

      //
      //  Assignment operations
      //
      AMatrix& operator = (const AMatrix&);
      AMatrix& operator = (const Element&); 
    
      //
      //  Selectors
      // 
      int rows() const                          { return M; }
      int columns() const                       { return N; }
      Element& operator () (int i, int j) const { return A[j * M + i]; }

      //
      // Scalar operations
      //
      friend AMatrix operator + (const Element&, const AMatrix&);
      friend AMatrix operator + (const AMatrix& a, const Element& b)
      { return b - a; }
      friend AMatrix operator - (const Element&, const AMatrix&);
      friend AMatrix operator - (const AMatrix&, const Element&);
      friend AMatrix operator * (const Element&, const AMatrix&);
      friend AMatrix operator * (const AMatrix& a, const Element& b)
      { return b * a; }
      friend AMatrix operator / (const AMatrix&, const Element&);
 
      //
      // In place scalar operations
      //
      AMatrix& operator += (const Element& x)
      { for (register int i = M * N - 1; i >= 0; i--) A[i] += x; return *this; }
      AMatrix& operator -= (const Element& x)
      { for (register int i = M * N - 1; i >= 0; i--) A[i] -= x; return *this; }
      AMatrix& operator *= (const Element& x)
      { for (register int i = M * N - 1; i >= 0; i--) A[i] *= x; return *this; }
      AMatrix& operator /= (const Element& x)
      { for (register int i = M * N - 1; i >= 0; i--) A[i] /= x; return *this; }

      //
      // AMatrix operations
      //
      friend AMatrix operator + (const AMatrix&, const AMatrix&);
      friend AMatrix operator - (const AMatrix&, const AMatrix&);
      friend AMatrix operator * (const AMatrix&, const AMatrix&);
      friend AMatrix product (const AMatrix * [], int);
      Element det();
      AMatrix inverse();

      //
      // In place matrix operations
      //
      AMatrix& operator += (const AMatrix& B)
      {  for (register int i = M * N - 1; i >= 0; i--) A[i] += B.A[i]; 
         return *this; 
      }
      AMatrix& operator -= (const AMatrix& B)
      {  for (register int i = M * N - 1; i >= 0; i--) A[i] -= B.A[i]; 
         return *this;
      }
      AMatrix& operator *= (const AMatrix&);
      void invert();

      //
      // Comparisons
      //
      friend int operator == (const AMatrix&, const AMatrix&);
      friend int operator != (const AMatrix& a, const AMatrix& b)
      { return ! a == b; }
   };

//
// Implementation 
//

template<class Element>
   AMatrix<Element>::Matrix(int row, int columns) : M(row), N(columns)
   {  A = new Element [row * columns]; }

template<class Element>
   AMatrix<Element>::Matrix(int row, int columns, const Element& x) 
      : M(row), N(columns)
   {  register int i = row * columns;
      A = new Element [i];
      for (i--; i >= 0; i--) A[i] = x;
   }

template<class Element>
   AMatrix<Element>::Matrix(const AMatrix<Element>& B)
   {  register int i = B.M * B.N;
      A = new Element [i];
      for (i--; i >= 0; i--) A[i] = B.A[i];
   }

template<class Element>
   int operator == (const AMatrix<Element>& a, const AMatrix<Element>& b)
   { if (a.M != b.M || a.N != b.N) return 0;
     for (register int i = a.M * a.N - 1; i >= 0; i--) 
        if (a.A[i] != b.A[i]) return 0;
     return 1;
   }

template<class Element>
   AMatrix<Element> operator + (const Element& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(b.M,b.N);
      for (register int i = b.M * b.N - 1; i >= 0; i--)
         B.A[i] = b.A[i] + a;
      return B;
   }

template<class Element>
   AMatrix<Element> operator - (const Element& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(b.M,b.N);
      for (register int i = b.M * b.N - 1; i >= 0; i--)
         B.A[i] = a - b.A[i];
      return B;
   }

template<class Element>
   AMatrix<Element> operator - (const AMatrix<Element>& a, const Element& b)
   {  AMatrix<Element> B(a.M,a.N);
      for (register int i = a.M * a.N - 1; i >= 0; i--)
         B.A[i] = a.A[i] - b;
      return B;
   }

template<class Element>
   AMatrix<Element> operator * (const Element& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(b.M,b.N);
      for (register int i = b.M * b.N - 1; i >= 0; i--)
         B.A[i] = a * b.A[i];
      return B;
   }

template<class Element>
   AMatrix<Element> operator / (const AMatrix<Element>& a, const Element& b)
   {  AMatrix<Element> B(a.M,a.N);
      for (register int i = a.M * a.N - 1; i >= 0; i--)
         B.A[i] = a.A[i] / b;
      return B;
   }

template<class Element>
   AMatrix<Element> operator+(const AMatrix<Element>& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(a.M,a.N);
      for (register int i = a.M * a.N - 1; i >= 0; i--)
         B.A[i] = a.A[i] + b.A[i];
      return B;
   }

template<class Element>
   AMatrix<Element> operator-(const AMatrix<Element>& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(a.M,a.N);
      for (register int i = a.M * a.N - 1; i >= 0; i--)
         B.A[i] = a.A[i] - b.A[i];
      return B;
   }

template<class Element>
   AMatrix<Element> operator*(const AMatrix<Element>& a, const AMatrix<Element>& b)
   {  AMatrix<Element> B(a.M,b.N);
      for (register int i = 0; i < a.M; i++) 
         for (register int j = 0; i < a.M; j++)
            for (register int k = 0; i < a.M; k++)
      ;
      return B;
   }

#endif
