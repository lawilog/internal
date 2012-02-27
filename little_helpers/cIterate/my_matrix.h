#define _NO_NAMESPACE
#define _NO_EXCEPTION

#include "matrix.h"
#define STD
typedef double type;
typedef matrix<type> Matrix;
#define TRYBEGIN()
#define CATCHERROR()

/*
#ifndef _NO_NAMESPACE 
using namespace std;
using namespace math;
#define STD std
#else
#define STD
#endif
 
#if !defined(_NO_TEMPLATE)
#  if defined(_MSC_VER)
#     if _MSC_VER > 1000
#        include <complex>
         typedef complex<double> type;
#     else
         typedef double type;
#     endif
#  elif defined(__BORLANDC__)
#     if defined(__WIN32__)
#        include <complex>
         typedef complex<double> type;
#     else
#        include <complex.h>
         typedef complex type;
#     endif
#  elif defined( __GNUG__ )
#       include <complex>
        typedef complex<double> type;
# elif defined( _SGI_BROKEN_STL )
# include <complex>
typedef std::complex<double> type;
#  endif
  typedef matrix<type> Matrix;
#else
   typedef matrix Matrix;
#endif

#ifndef _NO_EXCEPTION
#  define TRYBEGIN()	try {
#  define CATCHERROR()	} catch (const STD::exception& e) { \
                     cerr << "Error: " << e.what() << endl; }
#else
#  define TRYBEGIN()
#  define CATCHERROR()
#endif
*/
