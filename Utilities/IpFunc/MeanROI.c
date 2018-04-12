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
 *  this function calculates the mean of all pixels inside of a polygon
 */

/** @brief calculates the mean of all pixels inside of a polygon
 *
 *  The polygon is described by a sequence of points
 *
 *  @param pic_old    pointer to original image
 *  @param pol_x     vector with the x-coordinates of the points which form
 *              form the roi
 *  @param pol_y      vector with the y-coordinates of the points which form
 *              form the roi
 *  @param no_pts     number of points used to describe ROI
 *
 * REMARKS
 *  this function could just be used for 2D images
 *
 *  @return  mean of all greyvalues in ROI
 *
 * AUTHOR & DATE
 */

/* include files                                                       */

#include "mitkIpFuncP.h"

mitkIpFloat8_t mitkIpFuncMeanROI ( mitkIpPicDescriptor *pic_old,
                           mitkIpUInt4_t       *pol_x,
                           mitkIpUInt4_t       *pol_y,
                           mitkIpUInt4_t       no_pts ) ;
#ifndef DOXYGEN_IGNORE


#ifndef lint
  static char *what = { "@(#)mitkIpFuncMeanROI\t\tDKFZ (Dept. MBI)\t"__DATE__ };
#endif



/*definition of macros                                                 */

#define MAX( x, y ) ( x > y ) ? x : y  
#define MIN( x, y ) ( x < y ) ? x : y  
#define ROI( type, pic, pic_help, sum, count )                          \
{                                                                       \
   mitkIpBool_t     in;                                                     \
   mitkIpUInt4_t    i, j;                                                   \
   mitkIpUInt4_t    offset;                                                 \
                                                                        \
   for ( i = min_y; i <= max_y; i++ )                                   \
     {                                                                  \
        in = mitkIpFalse;                                                   \
        offset = i * pic->n[0] + min_x;                                 \
        for ( j = min_x; j <= max_x; j++ )                              \
          {                                                             \
             if ( (( mitkIpUInt1_t * )pic_help->data )[offset] && ( !in ) ) \
               in = mitkIpTrue;                                          \
             else if ( (( mitkIpUInt1_t * )pic_help->data )[offset] && ( in ) ) \
               {                                                        \
                  in = mitkIpFalse;                                         \
                  sum = sum + (( type * )pic->data )[offset];           \
                  count++;                                              \
               }                                                        \
                                                                        \
             if ( in )                                                  \
               {                                                        \
                  sum = sum + (( type * )pic->data )[offset];           \
                  count++;                                              \
               }                                                        \
                                                                        \
             offset++;                                                  \
          }                                                             \
     }                                                                  \
}

/*
** mitkIpFuncMeanROI
*/

mitkIpFloat8_t mitkIpFuncMeanROI ( mitkIpPicDescriptor *pic_old,
                           mitkIpUInt4_t       *pol_x,
                           mitkIpUInt4_t       *pol_y,
                           mitkIpUInt4_t       no_pts ) 
{
   mitkIpFloat8_t      mean;            /* mean of greyvalues in ROI        */
   mitkIpFloat8_t      sum=0;           /* sum  of greyvalues in ROI        */
   mitkIpFloat8_t      *a, *b;          /* Gerade y = ax+b                  */
   mitkIpPicDescriptor *pic_help;       /* contains edge of ROI             */
   mitkIpUInt4_t       min_x, max_x;    /* min, max x-coordinate of ROI     */
   mitkIpUInt4_t       min_y, max_y;    /* min, max y-coordinate of ROI     */
   mitkIpUInt4_t       i;               /* loop variable                    */
   mitkIpUInt4_t       count=0;         /* number of pixels in ROI          */
   mitkIpFloat8_t      diff;            /* difference between two points    */

   /* check image data                                                  */

   if ( _mitkIpFuncError ( pic_old ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );
   if ( pic_old->dim > 2 ) 
     {
        _mitkIpFuncSetErrno ( mitkIpFuncDIM_ERROR );
        return ( mitkIpFuncERROR );
     }

   /* calculate min. and max. coordiantes of ROI                        */

   min_x = pol_x[0];
   min_y = pol_y[0];
   max_x = pol_x[0];
   max_y = pol_y[0];
   for ( i = 1; i < no_pts; i++ )
     {
        min_x = MIN ( min_x, pol_x[i] );
        min_y = MIN ( min_y, pol_y[i] );
        max_x = MAX ( max_x, pol_x[i] );
        max_y = MAX ( max_y, pol_y[i] );
     }
   

   /* check whether ROI is in image                                     */

   /* Expression is always false.
   if ( min_x < 0 ) 
     {
        _mitkIpFuncSetErrno ( mitkIpFuncDATA_ERROR );
        return ( mitkIpFuncERROR );
     }
   */

   if ( max_x > pic_old->n[0] )
     {
        _mitkIpFuncSetErrno ( mitkIpFuncDATA_ERROR );
        return ( mitkIpFuncERROR );
     }

    /* Expression is always false.
   if ( min_y < 0 ) 
     {
        _mitkIpFuncSetErrno ( mitkIpFuncDATA_ERROR );
        return ( mitkIpFuncERROR );
     }
   */

   if ( max_y > pic_old->n[1] ) 
     {
        _mitkIpFuncSetErrno ( mitkIpFuncDATA_ERROR );
        return ( mitkIpFuncERROR );
     }

   /* allocate memory for a and b                                       */

   a = ( mitkIpFloat8_t * ) malloc ( no_pts * sizeof ( mitkIpFloat8_t ) );
   b = ( mitkIpFloat8_t * ) malloc ( no_pts * sizeof ( mitkIpFloat8_t ) );
  
   /* Geraden zwischen zwei benachbarten Punkten berechnen              */
  
   for ( i = 0; i < no_pts-1;  i++ )
     {
        diff = ( mitkIpFloat8_t ) pol_x[i+1] - ( mitkIpFloat8_t ) pol_x[i];
        if ( diff )
          {
            a[i] = ( ( mitkIpFloat8_t ) pol_y[i+1] - ( mitkIpFloat8_t ) pol_y[i] ) / diff;
            b[i] = ( ( mitkIpFloat8_t ) pol_y[i] - a[i] * ( mitkIpFloat8_t )pol_x[i] );
          }
        else
          {
            b[i] = 0.;
            a[i] = 0.;
           }
     }
   diff = ( mitkIpFloat8_t ) pol_x[no_pts-1] - ( mitkIpFloat8_t )  pol_x[0]; 
   if ( diff )
     {
        a[no_pts-1] = ( ( mitkIpFloat8_t ) pol_y[no_pts-1] - ( mitkIpFloat8_t ) pol_y[0] ) / diff;
        b[no_pts-1] = ( pol_y[no_pts-1] - a[no_pts-1] * pol_x[no_pts-1] );
     }
   else
     {
        b[no_pts-1] = 0.;
        a[no_pts-1] = 0.;
     }
   
  /* draw polygon to image                                               */
 
  pic_help = _mitkIpFuncDrawPoly ( pic_old, pol_x, pol_y, no_pts, a, b );
  if ( ! pic_help )
    {
       free ( a );
       free ( b );
       return ( mitkIpFuncERROR );
    }

  /* macro to calculate mean                                             */

  mitkIpPicFORALL_3 ( ROI, pic_old, pic_help, sum, count );

  mean = sum / count;

  free ( a );
  free ( b );
  mitkIpPicFree ( pic_help );

  return ( mean );

} 
#endif
