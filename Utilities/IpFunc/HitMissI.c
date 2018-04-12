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

/* performs the morphological hit and miss operator
 *
 * FUNCTION DECLARATION
 *  mitkIpPicDescriptor *_mitkIpFuncHitMissI( mitkIpPicDescriptor *pic_old,
 *                                    mitkIpPicDescriptor *pic_masks,
 *                                    mitkIpFuncFlagI_t    border )
 *
 * PARAMETERS
 *
 * RETURN VALUES
 *
 * AUTHOR & DATE
 *  Antje Schroeder	05.09.95
 *
 * UPDATES
 *  a short history of the file
 *
 *---------------------------------------------------------------------
 * COPYRIGHT (c) 1995 by DKFZ (Dept. MBI) HEIDELBERG, FRG
 */
#ifndef lint
  static char *what = { "@(#)mitkIpFuncHitMissI\t\tDKFZ (Dept. MBI)\t"__DATE__ };
#endif

/* include files                                                              */

#include "mitkIpFuncP.h"

/* definition of macros                                                       */

#define C_MASC( typ, pic_masks, m1, m2, end_m, beg_m1, beg_m2 )                \
{                                                                              \
  mitkIpUInt4_t     no_elem;                                                       \
  mitkIpUInt4_t     i;                        /* loop variable                  */ \
                                                                               \
  /* copy pic_masks to mask_1 and mask_2                                    */ \
                                                                               \
  for ( i = 0; i < end_m; i++ )                                                \
    {                                                                          \
       (( typ * )mask_1->data )[i] = (( typ * )pic_masks->data )[i + beg_m1];  \
       (( typ * )mask_2->data )[i] = (( typ * )pic_masks->data )[i + beg_m2];  \
    }                                                                          \
                                                                               \
  /* check mask data                                                        */ \
                                                                               \
  no_elem = _mitkIpPicElements ( mask_1 );                                         \
  for ( i = 0; i < no_elem; i++ )                                              \
    if ( (( typ * )mask_1->data )[i] != 0 &&                                   \
         (( typ * )mask_2->data )[i] != 0 )                                    \
      {                                                                        \
         mitkIpPicFree ( mask_1 );                                                 \
         mitkIpPicFree ( mask_2 );                                                 \
         mitkIpPicFree ( pic_1 );                                                  \
         _mitkIpFuncSetErrno ( mitkIpFuncUNFIT_ERROR );                                \
         return ( mitkIpFuncERROR );                                                   \
      }                                                                        \
                                                                               \
  /* compress masks                                                         */ \
                                                                               \
  m1 = _mitkIpFuncCompressM ( mask_1, pic_old, mitkIpFuncNoReflect, beg, end );         \
  m2 = _mitkIpFuncCompressM ( mask_2, pic_old, mitkIpFuncNoReflect, beg, end );         \
                                                                               \
}                                                                               

#define HITMISS( type_i, pic_old, pic_new, pic_inv )                           \
{                                                                              \
  type_i        help;                                                          \
  mitkIpUInt4_t     i;                       /* loop index                      */ \
  mitkIpUInt4_t     end_m;                   /* loop index                      */ \
  mitkIpUInt4_t     beg_m1;                  /*                                 */ \
  mitkIpUInt4_t     beg_m2;                  /*                                 */ \
  mitkIpUInt4_t     size[_mitkIpPicNDIM];        /*                                 */ \
  mitkIpInt4_t      ind[_mitkIpPicNDIM];         /* loop index vector               */ \
  mitkIpUInt4_t     off[_mitkIpPicNDIM];         /* offset vector                   */ \
  mitkIpFloat8_t    max, min;                /* max and min possible greyvalue  */ \
                                                                               \
  /* initialisation of vectors                                              */ \
                                                                               \
  size [0] = 1;                                                                \
  for ( i = 1; i < _mitkIpPicNDIM; i++ )                                           \
    size[i] = size[i-1] * pic_old->n[i-1];                                     \
  size[pic_old->dim] = 0;                                                      \
                                                                               \
                                                                               \
  /* calculate max. and min. possible greyvalues                            */ \
                                                                               \
  if ( _mitkIpFuncExtT ( pic_old->type, pic_old->bpe, &min, &max ) != mitkIpFuncOK )        \
    {                                                                          \
       mitkIpPicFree ( mask_1 );                                                   \
       mitkIpPicFree ( mask_2 );                                                   \
       mitkIpPicFree ( pic_1 );                                                    \
       return ( mitkIpFuncERROR );                                                     \
    }                                                                          \
                                                                               \
  /* transformation of image                                                */ \
                                                                               \
  end_m  = _mitkIpPicElements ( pic_masks ) / pic_masks->n[dim] ;                  \
  for ( j = 0; j < pic_masks->n[dim] / 2; j++ )                                \
    {                                                                          \
       /* copy masks and compress them                                      */ \
                                                                               \
       beg_m1 = 2 * j * end_m;                                                 \
       beg_m2 = beg_m1 + end_m;                                                \
       mitkIpPicFORALL_5 ( C_MASC, pic_masks, m1, m2, end_m, beg_m1, beg_m2 );     \
                                                                               \
       for ( ind[7] = beg[7]; ind[7] < end[7]; ind[7]++ )                      \
       {                                                                       \
         off[7] = ind[7] * size[7];                                            \
         for ( ind[6] = beg[6]; ind[6] < end[6]; ind[6]++ )                    \
         {                                                                     \
           off[6] = ind[6] * size[6] + off[7];                                 \
           for ( ind[5] = beg[5]; ind[5] < end[5]; ind[5]++ )                  \
           {                                                                   \
             off[5] = ind[5] * size[5] + off[6];                               \
             for ( ind[4] = beg[4]; ind[4] < end[4]; ind[4]++ )                \
             {                                                                 \
               off[4] = ind[4] * size[4] + off[5];                             \
               for ( ind[3] = beg[3]; ind[3] < end[3]; ind[3]++ )              \
               {                                                               \
                 off[3] = ind[3] * size[3] + off[4];                           \
                 for ( ind[2] = beg[2]; ind[2] < end[2]; ind[2]++ )            \
                 {                                                             \
                   off[2] = ind[2] * size[2] + off[3];                         \
                   for ( ind[1] = beg[1]; ind[1] < end[1]; ind[1]++ )          \
                   {                                                           \
                     off[1] = ind[1] * size[1] + off[2];                       \
                     off[0] = beg[0] + off[1];                                 \
                     for ( ind[0] = beg[0]; ind[0] < end[0]; ind[0]++ )        \
                     {                                                         \
                       help = (( type_i * )                                    \
                                   pic_old->data )[off[0]+ m1->off_vekt[0]];   \
                       for ( i = 1; i < m1->length; i++ )                      \
                         {                                                     \
                           help = help &&                                      \
                                (( type_i * )pic_old->data )                   \
                                                    [m1->off_vekt[i]+off[0]];  \
                         }                                                     \
                       for ( i = 0; i < m2->length; i++ )                      \
                         {                                                     \
                           help =   help &&                                    \
                                (( type_i * )pic_inv->data )                   \
                                                    [m2->off_vekt[i]+off[0]];  \
                         }                                                     \
                       (( type_i * )pic_new->data )[off[0]] = (  (( type_i * ) \
                            pic_new->data )[off[0]] || ( type_i ) help ) * max;\
                       off[0]++;                                               \
                     }                                                         \
                   }                                                           \
                 }                                                             \
               }                                                               \
             }                                                                 \
           }                                                                   \
         }                                                                     \
       }                                                                       \
       free ( m1->off_vekt );                                                  \
       free ( m1->mask_vekt );                                                 \
       free ( m1 );                                                            \
       free ( m2->off_vekt );                                                  \
       free ( m2->mask_vekt );                                                 \
       free ( m2 );                                                            \
    }                                                                          \
}


/* -------------------------------------------------------------------------  */
/*
** mitkIpFuncHitMissI
*/
/* -------------------------------------------------------------------------  */

 mitkIpPicDescriptor *_mitkIpFuncHitMissI ( mitkIpPicDescriptor *pic_old,
                                    mitkIpPicDescriptor *pic_masks, 
                                    mitkIpFuncFlagI_t    border )
{
   mitkIpPicDescriptor *pic_inv;         /* pointer to the inverted image         */ 
   mitkIpPicDescriptor *pic_1;           /* image after hit and miss              */ 
   mitkIpPicDescriptor *mask_1;          /* hit mask                              */ 
   mitkIpPicDescriptor *mask_2;          /* miss mask                             */ 
   mitkIpInt4_t        beg[_mitkIpPicNDIM];  /*                                       */
   mitkIpInt4_t        end[_mitkIpPicNDIM];  /*                                       */
   mitkIpFuncMasc_t    *m1, *m2;         /* compressed masks                      */
   mitkIpUInt4_t       dim;              /* dimension of mask                     */
   mitkIpUInt4_t       j;                /* loop variable                         */

   /* check image data and mask data                                          */

   if ( _mitkIpFuncError ( pic_old ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );
   if ( _mitkIpFuncError ( pic_masks ) != mitkIpFuncOK ) return ( mitkIpFuncERROR );

   /* allocate memory for masks                                               */

   dim = pic_masks->dim - 1;                                                     
   mask_1 = mitkIpPicCopyHeader ( pic_masks, NULL );
   mask_1->dim = dim;                      
   if ( mask_1 == NULL ) 
     {
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );
        return ( mitkIpFuncERROR );
     }
   mask_1->data = malloc ( _mitkIpPicSize ( mask_1 ) );
   if ( mask_1->data == NULL )
     {
        mitkIpPicFree ( mask_1 );
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );
        return ( mitkIpFuncERROR );
     }
   mask_2 = mitkIpPicCopyHeader ( mask_1, NULL );
   if ( mask_2 == NULL )
     {
        mitkIpPicFree ( mask_1 );
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );
        return ( mitkIpFuncERROR );
     }
   mask_2->data = malloc ( _mitkIpPicSize ( mask_2 ) );
   if ( mask_2->data == NULL ) 
     {
        mitkIpPicFree ( mask_1 );
        mitkIpPicFree ( mask_2 );
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );
        return ( mitkIpFuncERROR );
     }

   /* allocate images                                                         */

   if ( border == mitkIpFuncBorderOld )
     {
        pic_1 = mitkIpPicClone ( pic_old );
        memset ( pic_1->data, 0, _mitkIpPicElements ( pic_1 ) );
     }
   else if ( border == mitkIpFuncBorderZero )
     {
        pic_1 = mitkIpPicCopyHeader ( pic_old, 0 );
        pic_1->data = calloc ( _mitkIpPicElements ( pic_1 ), pic_1->bpe/8  );
     }
   else
     {
        mitkIpPicFree ( mask_1 );
        mitkIpPicFree ( mask_2 );
        _mitkIpFuncSetErrno ( mitkIpFuncFLAG_ERROR );
        return ( mitkIpFuncERROR );
     }
 
   if ( pic_1 == NULL )
     {
        mitkIpPicFree ( mask_1 );
        mitkIpPicFree ( mask_2 );
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );                 
        return ( mitkIpFuncERROR );
     }

   if ( pic_1->data == NULL )
     {
        mitkIpPicFree ( mask_1 );
        mitkIpPicFree ( mask_2 );
        mitkIpPicFree ( pic_1 );
        _mitkIpFuncSetErrno ( mitkIpFuncMALLOC_ERROR );                 
        return ( mitkIpFuncERROR );
     }

   pic_inv = mitkIpFuncInv ( pic_old, NULL );
   if ( pic_inv == NULL )
     {
        mitkIpPicFree ( mask_1 );
        mitkIpPicFree ( mask_2 );
        mitkIpPicFree ( pic_1 );
     }

   mitkIpPicFORALL_2 ( HITMISS, pic_old, pic_1, pic_inv );

   mitkIpPicFree ( pic_inv );
   mitkIpPicFree ( mask_1 );
   mitkIpPicFree ( mask_2 );

   return ( pic_1 );
}
