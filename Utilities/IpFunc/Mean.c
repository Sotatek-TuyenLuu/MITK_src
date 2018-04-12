/*****************************************************************************

 Copyright (c) 1993-2000,  Div. Medical and Biological Informatics, 
 Deutsches Krebsforschungszentrum, Heidelberg, Germany
 All rights reserved.

 Redistribution and use in source and binary forms, with or without 
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

 - All advertising materials mentioning features or use of this software must 
   display the following acknowledgement: 
          
     "This product includes software developed by the Div. Medical and 
      Biological Informatics, Deutsches Krebsforschungszentrum, Heidelberg, 
      Germany."

 - Neither the name of the Deutsches Krebsforschungszentrum nor the names of 
   its contributors may be used to endorse or promote products derived from 
   this software without specific prior written permission. 

   THIS SOFTWARE IS PROVIDED BY THE DIVISION MEDICAL AND BIOLOGICAL
   INFORMATICS AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE DIVISION MEDICAL AND BIOLOGICAL INFORMATICS,
   THE DEUTSCHES KREBSFORSCHUNGSZENTRUM OR CONTRIBUTORS BE LIABLE FOR 
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
   IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN 
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

 Send comments and/or bug reports to:
   mbi-software@dkfz-heidelberg.de

*****************************************************************************/

/**@file
 *    this function calculates the mean greyvalue of all greyvalues
 *    in an image
 */

/**   this function calculates the mean greyvalue of all greyvalues
 *    in an image
 *
 *  
 *    @param pic    pointer to the image 
 *  
 *     @return  mean greyvalue
 *
 * AUTHOR & DATE
 */

/* include-files                                              */

#include "mitkIpFuncP.h"

mitkIpFloat8_t mitkIpFuncMean ( mitkIpPicDescriptor *pic );

#ifndef DOXYGEN_IGNORE
 
#ifndef lint
  static char *what = { "@(#)mitkIpFuncMean\t\tDKFZ (Dept. MBI)\t"__DATE__ };
#endif


 
/* definition of extreme value macro                          */

#define MEAN( type, pic, mean )                                \
  {                                                            \
    mitkIpUInt4_t   i, no_elem;                                    \
                                                               \
    mean = 0.;                                                 \
    no_elem = _mitkIpPicElements ( pic );                          \
                                                               \
    for ( i = 0; i < no_elem; i++ )                            \
      {                                                        \
        mean = ( ( type * ) pic->data ) [i] + mean;            \
      }                                                        \
    mean = mean /  _mitkIpPicElements ( pic );                     \
  }
 
/* ========================================================== */
/*
*/
/* ========================================================== */

mitkIpFloat8_t mitkIpFuncMean ( mitkIpPicDescriptor *pic )
{

  mitkIpFloat8_t mean = 0.0;            

  /* check data                                               */ 

  if ( _mitkIpFuncError ( pic ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );

  mitkIpPicFORALL_1( MEAN, pic, mean )

  return( mean );
}
#endif

