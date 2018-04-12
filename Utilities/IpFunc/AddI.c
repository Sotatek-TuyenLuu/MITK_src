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

/** @file
*   this function adds two images
*/

/** @brief adds two images
 *  @param pic_1 pointer to the first image
 *  @param pic_2 pointer to the second image
 *  @param keep tells whether the image type could be changed when
 *                necessary
 *  @arg @c mitkIpFuncNoKeep : image data type could be changed
 *  @arg @c mitkIpFuncKeep   : image data type of original pictures is
 *                             kept (if there will be an over-/underflow
 *                             the max. or min. possible greyvalue is taken)
 *  @param pic_return memory used to store return image ( if pic_return == NULL
 *                new memory is allocated )
 *
 *  @return pointer to the new image
 *
 * AUTHOR & DATE
 */

/* include-Files                                                        */

#include "mitkIpFuncP.h"

mitkIpPicDescriptor *mitkIpFuncAddI ( mitkIpPicDescriptor *pic_1,
                              mitkIpPicDescriptor *pic_2,
                              mitkIpFuncFlagI_t   keep,
                              mitkIpPicDescriptor *pic_return );

#ifndef DOXYGEN_IGNORE

#ifndef lint
  static char *what = { "@(#)mitkIpFuncAddI\t\tDKFZ (Dept. MBI)\t"__DATE__ };
#endif


/* definition of macros                                                 */

#define ADDI( type_1, pic_1, pic_2, pic_new )                            \
{                                                                        \
  mitkIpPicFORALL_3 ( ADDI2, pic_new, pic_1, pic_2, type_1 );                \
}                                                                        \
 

#define ADDI2( type_n, pic_new, pic_1, pic_2, type_1 )                   \
{                                                                        \
  mitkIpUInt4_t  i;                                                          \
  mitkIpUInt4_t  no_elem;                                                    \
                                                                         \
  no_elem =  _mitkIpPicElements ( pic_1 );                                   \
  for ( i = 0; i < no_elem; i++ )                                        \
    {                                                                    \
       (( type_n * ) pic_new->data ) [i] = ( type_n )                    \
             ( (( type_1 * ) pic_1->data ) [i] +                         \
               (( type_1 * ) pic_2->data ) [i] );                        \
    }                                                                    \
}

#define ADDI3( type_n, pic_1, pic_2, pic_new )                           \
{                                                                        \
  mitkIpUInt4_t  i;                                                          \
  mitkIpUInt4_t  no_elem;                                                    \
  type_n     help;                                                       \
  type_n     help2;                                                      \
                                                                         \
  no_elem =  _mitkIpPicElements ( pic_1 );                                   \
  for ( i = 0; i < no_elem; i++ )                                        \
    {                                                                    \
       help  = (( type_n * ) pic_1->data ) [i];                          \
       help2 = (( type_n * ) pic_2->data ) [i];                          \
       (( type_n * ) pic_new->data ) [i] =                               \
          ( max_gv > ( mitkIpFloat8_t ) help + ( mitkIpFloat8_t ) help2  ) ?     \
             (( min_gv < ( mitkIpFloat8_t ) help + ( mitkIpFloat8_t ) help2 ) ?  \
                 ( (type_n)help + (type_n)help2 ) : ( type_n ) min_gv ) :\
             ( type_n ) max_gv;                                          \
    }                                                                    \
}



/* -------------------------------------------------------------------  */
/*
*/
/* -------------------------------------------------------------------  */

mitkIpPicDescriptor *mitkIpFuncAddI ( mitkIpPicDescriptor *pic_1,
                              mitkIpPicDescriptor *pic_2,
                              mitkIpFuncFlagI_t   keep,
                              mitkIpPicDescriptor *pic_return )
{

  mitkIpPicDescriptor *pic_new;         /* pointer to new image             */
  mitkIpUInt4_t       i;                /* loop index                       */
  mitkIpFloat8_t      max_gv;           /* max. possible greyvalue          */
  mitkIpFloat8_t      min_gv;           /* min. possible greyvalue          */
  mitkIpFloat8_t      min1, max1;       /* extreme greyvalues of 1. image   */ 
  mitkIpFloat8_t      min2, max2;       /* extreme greyvalues of 2. image   */
  mitkIpFloat8_t      smin, smax;       /* product of extreme greyvalues    */


  /* ckeck whether data are correct                                     */

  if ( _mitkIpFuncError ( pic_1 ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );
  if ( _mitkIpFuncError ( pic_2 ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );

  /* check whether images have the same size                            */

  if ( ( pic_1->type != pic_2->type ) || ( pic_1->bpe != pic_2->bpe ) )
    {
      _mitkIpFuncSetErrno ( mitkIpFuncUNFIT_ERROR );         
      return NULL;
    }
  if ( pic_1->dim == pic_2->dim )
    for ( i = 0; i < _mitkIpPicNDIM; i++ )
      {
        if ( pic_1->n[i] != pic_2->n[i] )
          {
             _mitkIpFuncSetErrno ( mitkIpFuncUNFIT_ERROR );
             return NULL;
          }
      }
  else
    {
       _mitkIpFuncSetErrno ( mitkIpFuncUNFIT_ERROR );
       return NULL;
    }

  /* calculate max. and min. possible greyvalues for data type of images*/

  if ( _mitkIpFuncExtT ( pic_1->type, pic_1->bpe, &min_gv, &max_gv ) != mitkIpFuncOK )
    return ( mitkIpFuncERROR );

  /* find out data type of new iamge                                    */

  if ( keep == mitkIpFuncKeep )
    {
       pic_new = _mitkIpFuncMalloc ( pic_1, pic_return, mitkIpOVERWRITE );     
       if ( pic_new == NULL ) return ( mitkIpFuncERROR );
    }
  else if ( keep == mitkIpFuncNoKeep )
    {
       /* calculate max. and min. greyvalues of both images             */

       if ( mitkIpFuncExtr ( pic_1, &min1, &max1 ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );
       if ( mitkIpFuncExtr ( pic_2, &min2, &max2 ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );

       smax      = max1 + max2;
       smin      = min1 + min2;

       /* change image type of images of type mitkIpPicInt                  */

       if ( pic_1->type == mitkIpPicInt )
         {
           if ( smax < max_gv && smin > min_gv ) 
             {
                pic_new = mitkIpPicCopyHeader ( pic_1, NULL );
             }
           else
             {
                pic_new       = mitkIpPicCopyHeader ( pic_1, NULL );
                pic_new->type = mitkIpPicFloat;
                pic_new->bpe  = 64;
                _mitkIpFuncExtT ( pic_new->type, pic_new->bpe, &min_gv, &max_gv );
             }
         }

       /* change image type of images of type mitkIpPicUInt                 */

       else if ( pic_1->type == mitkIpPicUInt )
         {
           if ( smax < max_gv && smin > min_gv )
             {
                pic_new = mitkIpPicCopyHeader ( pic_1, NULL );
             }
           else
             {
                pic_new = mitkIpPicCopyHeader ( pic_1, NULL );
                pic_new->type = mitkIpPicInt;
                pic_new->bpe  = 16;
                _mitkIpFuncExtT ( pic_new->type, pic_new->bpe, &min_gv, &max_gv );
                if ( smax > max_gv || smin < min_gv )
                  {
                     pic_new->type = mitkIpPicFloat;
                     pic_new->bpe  = 64;
                     _mitkIpFuncExtT ( pic_new->type, pic_new->bpe, &min_gv, &max_gv );
                  }
             }
         } 

       /* change image type of images of type mitkIpPicUInt                 */
 
       else if ( pic_1->type == mitkIpPicFloat )
         {
            pic_new = mitkIpPicCopyHeader ( pic_1, NULL );
         }
       else 
         {     
            _mitkIpFuncSetErrno ( mitkIpFuncTYPE_ERROR );
            return ( mitkIpFuncERROR );
         }
    }
  else
    {
       _mitkIpFuncSetErrno ( mitkIpFuncFLAG_ERROR );
       return ( mitkIpFuncERROR );
    }


  if ( pic_new == NULL )
    {
       _mitkIpFuncSetErrno ( mitkIpFuncPICNEW_ERROR );
       return ( mitkIpFuncERROR );
    }
    
  if ( keep == mitkIpFuncNoKeep )
    pic_new->data = malloc ( _mitkIpPicSize  ( pic_new ) );
  if ( pic_new->data == NULL )
    {
       mitkIpPicFree ( pic_new );
       _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );
       return ( mitkIpFuncERROR );
    }

  /* macro to invert the picture (for all data types)                   */

  if ( keep == mitkIpFuncNoKeep )
    mitkIpPicFORALL_2 ( ADDI, pic_1, pic_2, pic_new )
  else if ( keep == mitkIpFuncKeep )
    mitkIpPicFORALL_2 ( ADDI3, pic_1, pic_2, pic_new )

  /* Copy Tags */

  mitkIpFuncCopyTags(pic_new, pic_1);

  return pic_new;
}
#endif

