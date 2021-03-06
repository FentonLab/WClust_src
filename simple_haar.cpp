// $Id: simple_haar.cpp,v 1.1 2008/04/01 06:08:48 samn Exp $ 
#include "stdafx.h"
#include "simple_haar.h"

/**
 *
<p>
  Class simple_haar

<p>
   This object calcalculates the "ordered fast Haar wavelet
   transform".  The algorithm used is the a simple Haar wavelet
   algorithm that does <u>not</u> calculate the wavelet transform
   in-place.  The function works on Java double values.
<p>
   The wavelet_calc function is passed an <b>array</b> of doubles from
   which it calculates the Haar wavelet transform.  The transform is
   not calculated in place.  The result consists of a single value and
   a Vector of coefficients arrays, ordered by increasing frequency.
   The number of data points in the data used to calculate the wavelet
   must be a power of two.
<p>
   The Haar wavelet transform is based on calculating the Haar step
   function and the Haar wavelet from two adjacent values.  For
   an array of values S0, S1, S2 .. Sn, the step function and
   wavelet are calculated as follows for two adjacent points,
   S0 and S1:

<pre>
      <i>HaarStep</i> = (S0 + S1)/2  <i>// average of S0 and S1</i>
      <i>HaarWave</i> = (S0 - S1)/2  <i>// average difference of S0 and S1</i>
</pre>

<p>
   This yields two vectors: <b>a</b>, which contains the
   <i>HaarStep</i> values and <b>c</b>, which contains the
   <i>HaarWave</i> values.

<p> The result of the <tt>wavelet_calc</tt> is the single Haar value
    and a set of coefficients.  There will be ceil( log<sub>2</sub>(
    values.length() )) coefficients.

@author Ian Kaplan

@see <i>Wavelets Made Easy by Yves Nieverglt, Birkhauser, 1999</i>


<h4>
   Copyright and Use
</h4>

<p>
   You may use this source code without limitation and without
   fee as long as you include:
</p>
<blockquote>
     This software was written and is copyrighted by Ian Kaplan, Bear
     Products International, www.bearcave.com, 2001.
</blockquote>
<p>
   This software is provided "as is", without any warrenty or
   claim as to its usefulness.  Anyone who uses this source code
   uses it at their own risk.  Nor is any support provided by
   Ian Kaplan and Bear Products International.
<p>
   Please send any bug fixes or suggested source changes to:
<pre>
     iank@bearcave.com
</pre>


 */

//class simple_haar : public wavelet_base  {
//  double haar_value;  // the final Haar step value
//  vector< vector< double > > coef;        // The Haar coefficients
//  vector<double> data;

/**
 *
<p>
   Calculate the Haar wavelet transform
   (the ordered fast Haar wavelet tranform).
   This calculation is <u>not</u> done in place.

<p>
  @param values
         a <tt>values</tt>: an array of double
         values on which the Haar transform is
         applied.

 */

  void simple_haar::wavelet_calc( vector<double>& values )
  {

    if (values.size() ) {
      data = values;
      coef = vector< vector<double> >();
      haar_value = haar_calc( values );
      reverseCoef();
    }
  } // wavelet_calc


  /**

    The Haar transform coefficients are generated from the longest
    coefficient vector (highest frequency) to the shortest (lowest
    frequency).  However, the reverse Haar transform and the display
    of the values uses the coefficients from the lowest to the
    highest frequency.  This function reverses the coefficient
    order, so they will be ordered from lowest to highest frequency.

   */

  void simple_haar::reverseCoef() {
    int size = coef.size();

    for (int i = 0, j = size-1; i < j; i++, j--) {
      vector<double> tmp = coef.at(i);
      coef.at(i) = coef.at(j); //setElementAt(coef.elementAt(j), i);
      coef.at(j) = tmp; //coef.setElementAt(tmp, j);
    } // for
  } // reverseCoef



  /**
   *

    Recursively calculate the Haar transform.  The result
    of the Haar transform is a single integer value
    and a Vector of coefficients.  The coefficients are
    calculated from the highest to the lowest frequency.
<p>
    The number of elements in <tt>values</tt> must be a power of two.

   */
  double simple_haar::haar_calc( vector<double>& values )
  {
    double retVal;

    vector<double> a(values.size()/2);
    vector<double> c(values.size()/2);

	int i,j;

    for (i = 0, j = 0; i < values.size(); i += 2, j++) {
      a[j] = (values[i] + values[i+1])/2;
      c[j] = (values[i] - values[i+1])/2;
    }
    coef.push_back( c );

    if (a.size() == 1)
      retVal = a[0];
    else
      retVal = haar_calc( a );

    return retVal;
  } // haar_calc


  /**
   *

<p>
     Calculate the inverse haar transform from the coefficients
     and the Haar value.
<p>
     The inverse function will overwrite the original data
     that was used to calculate the Haar transform.  Since this
     data is initialized by the caller, the caller should
     make a copy if the data should not be overwritten.
<p>
     The coefficients are stored in in a Java <tt>Vector</tt>
     container.  The length of the coefficient arrays is ordered in
     powers of two (e.g., 1, 2, 4, 8...).  The inverse Haar function
     is calculated using a butterfly pattern to write into the data
     array.  An initial step writes the Haar value into data[0].  In
     the case of the example below this would be

<pre>
     data[0] = 5.0;
</pre>
<p>
     Then a butterfly pattern is shown below.  Arrays indices start at
     0, so in this example <tt>c[1,1] is the second element of the
     second coefficient vector.

<pre>
wavelet:
{[5.0];
-3.0;
0.0, -1.0;
1.0, -2.0, 1.0, 0.0}

tmp = d[0];
d[0] = tmp + c[0, 0]
d[4] = tmp - c[0, 0]

tmp = d[0];
d[0] = tmp + c[1, 0]
d[2] = tmp - c[1, 0]
tmp = d[4];
d[4] = tmp + c[1, 1]
d[6] = tmp - c[1, 1]

tmp = d[0];
d[0] = tmp + c[2, 0]
d[1] = tmp - c[2, 0]
tmp = d[2];
d[2] = tmp + c[2, 1]
d[3] = tmp - c[2, 1]
tmp = d[4];
d[4] = tmp + c[2, 2]
d[5] = tmp - c[2, 2]
tmp = d[6];
d[6] = tmp + c[2, 3]
d[7] = tmp - c[2, 3]
</pre>

   */

  void simple_haar::inverse() {
    if (data.size() && coef.size()) {
      int len = data.size();

      data[0] = haar_value;

      if (len > 0) {
	// System.out.println("inverse()");
		byte log = binary::log2( len );

		len = binary::power2( log );  // calculation must be on 2 ** n values

	int vec_ix = 0;
	int last_p = 0;
	byte p_adj = 1;

        for (byte l = (byte)(log-1); l >= 0; l--) {

		int p = binary::power2( l );
	  vector<double> c = coef.at( vec_ix );

	  int coef_ix = 0;
          for (int j = 0; j < len; j++) {
            int a_1 = p * (2 * j);
	    int a_2 = p * ((2 * j) + 1);

            if (a_2 < len) {
	      double tmp = data[a_1];
	      data[ a_1 ] = tmp + c[coef_ix];
	      data[ a_2 ] = tmp - c[coef_ix];
	      coef_ix++;
            }
            else {
              break;
            }
          } // for j
	  last_p = p;
	  p_adj++;
	  vec_ix++;
        } // for l
      }

    }
  } // inverse


  /**
      Print the simple Haar object (e.g, the
      final Haar step value and the coefficients.

   */
  void simple_haar::pr() {
    if (coef.size()) {
      printf("{[%.4f]",haar_value);
      int size = coef.size();
      vector<double> a;

      for (int i = 0; i < size; i++) {
	printf(";");
	a = coef.at(i);
	for (int j = 0; j < a.size(); j++) {
	  printf( "%.4f", a[j] );
	  if (j < a.size()-1) {
	    printf(", ");
	  }
	} // for j
      } // for i
      printf("}\n");
    }
  } // pr


  /**
   *

<p>
     Print the data values.

<p>
     The <tt>pr()</tt> method prints the coefficients in increasing
     frequency.  This function prints the data values which were
     used to generate the Haar transform.

   */
  void simple_haar::pr_values() {
    if (data.size()) {
      printf("{");
	  int i;
      for (i = 0; i < data.size(); i++) {
	printf( "%.4f", data[i] );
	if (i < data.size()-1)
	  printf(", ");
      }
      printf("}\n");
    }
  } // pr_values


//}; // simple_haar


/**
   Test code for the simple_haar.java wavelets code.

   To compile make sure that ".." is in the CLASSPATH.  For
   example, on UNIX (or with the Cygnus Bash shell)

      setenv CLASSPATH ..:$CLASSPATH

   Compile commmand:

      javac simple_haar_test.java
      jvc   simple_haar_test.java

   To run enter:

       jview simple_haar_test
       java  simple_haar_test

 */

  /**
    Print an array of doubles
   */
  void pr_vals( vector<double> vals ) {
    if (vals.size()) {
      for (int i = 0; i < vals.size(); i++) {
	printf( "%.4f", vals[i] );
	if (i < vals.size()-1)
	  printf(", ");
      }
      printf("\n");
    }
  } // pr_vals


  /**
     Test the simple_haar wavelet code, using the <i>vals</i>
     argument.
   */
  void wavelet_test( vector<double> vals )
  {
    simple_haar haar;

    printf("test data: \n");
    pr_vals( vals );
	printf("\n");

    haar.wavelet_calc( vals );
    printf("wavelet coefficients, ordered by increasing frequency:\n");
    haar.pr();
    printf("\n");

    printf("after calculating inverse Haar transform:\n");
    haar.inverse();
    haar.pr_values();
    printf("\n");
  } // wavelet_test


   void wavelet_test_main() {
      vector<double> vals;
	  vals.push_back(3.0);
	  vals.push_back(1.0);
	  vals.push_back(0.0);
	  vals.push_back(4.0);
	  vals.push_back(8.0);
	  vals.push_back(6.0);
	  vals.push_back(9.0);
	  vals.push_back(9.0);

      wavelet_test( vals );

      vector<double> vals2;
	  vals2.push_back(32.0);vals2.push_back(10.0);vals2.push_back(20.0);vals2.push_back(38.0);
			 vals2.push_back(37.0);vals2.push_back(28.0);vals2.push_back(38.0);vals2.push_back(34.0);
			 vals2.push_back(18.0);vals2.push_back(24.0);vals2.push_back(18.0);vals2.push_back(9.0);
			 vals2.push_back(23.0);vals2.push_back(24.0);vals2.push_back(28.0);vals2.push_back(34.0);
      wavelet_test( vals2 );
  } // wavelet_main_test


