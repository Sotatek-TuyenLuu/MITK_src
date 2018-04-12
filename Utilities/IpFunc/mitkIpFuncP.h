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


/*
 * mitkIpFuncP.h
 *---------------------------------------------------------------
 * DESCRIPTION
 *   contains the function prototypes, type definitions  and 
 *   includes for the image processing functions
 *
 * AUTHOR
 *   Antje Schroeder
 *
 * UPDATES
 *
 *---------------------------------------------------------------
 * COPYRIGHT (c) 1995 by DKFZ (Dept. MBI) Heidelberg, FRG
 */


#ifndef _mitkIpFuncP_h
#define _mitkIpFuncP_h

/* include files */

#include "mitkIpFunc.h"

/* type definitions */

typedef enum
  {
    mitkIpFuncEroF       = 0,
    mitkIpFuncDilaF      = 1,
    mitkIpFuncOpenF      = 2,
    mitkIpFuncCloseF     = 3,
    mitkIpFuncFlagF_MAX
  } _mitkIpFuncFlagF_t;
 
typedef struct
  { 
     mitkIpUInt4_t   length;
     mitkIpInt4_t    *off_vekt;
     mitkIpFloat8_t  *mask_vekt;
  }  mitkIpFuncMasc_t;

/* definition of macros */

#define mitkIpFuncCASE_FOR( pic, dim, mitkIpFuncSourceIndex )\
    case dim: for( mitkIpFuncSourceIndex[dim-1]=0; \
                   mitkIpFuncSourceIndex[dim-1] < pic->n[dim-1]; \
                   mitkIpFuncSourceIndex[dim-1]++ \
                 )

#define mitkIpFuncFORALL( type, pic, pic_return, \
                  mitkIpFuncSourceIndex, mitkIpFuncResultOffset, mitkIpFuncResultFunction )\
  {\
  mitkIpUInt4_t mitkIpFuncSourceOffset=0;\
  mitkIpUInt4_t i;\
  for( i=0; i<_mitkIpPicNDIM; i++) index[i] = 0;\
  for( i=pic->dim; i<_mitkIpPicNDIM; i++) pic->n[i] = 0;\
  for( i=pic_return->dim; i<_mitkIpPicNDIM; i++) pic_return->n[i] = 0;\
  switch( pic->dim )\
    {\
      default:\
        { \
          fprintf( stderr,\
          "sorry, only 1 to 8 dimensional data are supported.\n"); \
          pic_return = NULL;\
          break;\
        }\
      mitkIpFuncCASE_FOR( pic, 8, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 7, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 6, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 5, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 4, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 3, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 2, mitkIpFuncSourceIndex )\
      mitkIpFuncCASE_FOR( pic, 1, mitkIpFuncSourceIndex )\
        {\
          mitkIpFuncResultFunction;\
          ((type *)pic_return->data)[ mitkIpFuncResultOffset ]    \
               = ((type *)pic->data)[ mitkIpFuncSourceOffset ] ;  \
          mitkIpFuncSourceOffset++;\
        }\
    }\
  } 


/* function prototypes */


mitkIpUInt4_t _mitkIpFuncBox2d ( mitkIpPicDescriptor *pic_old,
                         mitkIpUInt4_t       **beg,
                         mitkIpUInt4_t       **end );

mitkIpUInt4_t _mitkIpFuncBox3d ( mitkIpPicDescriptor *pic_old,
                         mitkIpUInt4_t       **beg,
                         mitkIpUInt4_t       **end );

mitkIpUInt4_t       _mitkIpFuncError   ( mitkIpPicDescriptor *pic );

mitkIpPicDescriptor *_mitkIpFuncDrawPoly( mitkIpPicDescriptor *pic_old,        
                                 mitkIpUInt4_t       *pol_x,   
                                 mitkIpUInt4_t       *pol_y,    
                                 mitkIpUInt4_t       no_pts,
                                 mitkIpFloat8_t      *a,
                                 mitkIpFloat8_t      *b );

mitkIpPicDescriptor *_mitkIpFuncOpCl   ( mitkIpPicDescriptor *pic_old,
                                 mitkIpPicDescriptor *pic_mask,   
                                 _mitkIpFuncFlagF_t   kind,
                                 mitkIpFuncFlagI_t    border );

mitkIpPicDescriptor *_mitkIpFuncMorph  ( mitkIpPicDescriptor *pic_old,
                                 mitkIpPicDescriptor *pic_mask,
                                 _mitkIpFuncFlagF_t   kind,
                                 mitkIpFuncFlagI_t    border );

mitkIpFuncMasc_t *_mitkIpFuncCompressM ( mitkIpPicDescriptor *mask,   
                                 mitkIpPicDescriptor *pic_old,
                                 mitkIpFuncFlagI_t   kind,
                                 mitkIpInt4_t        beg[_mitkIpPicNDIM],  
                                 mitkIpInt4_t        end[_mitkIpPicNDIM] );

mitkIpInt4_t        _mitkIpFuncExtT    ( mitkIpPicType_t type,   
                                 mitkIpUInt4_t    bpe,
                                 mitkIpFloat8_t   *min_gv,
                                 mitkIpFloat8_t   *max_gv );


mitkIpPicDescriptor *_mitkIpFuncScNN   ( mitkIpPicDescriptor *pic_old,
                                 mitkIpPicDescriptor *pic_new );

mitkIpPicDescriptor *_mitkIpFuncScBL   ( mitkIpPicDescriptor *pic_old,
                                 mitkIpPicDescriptor *pic_new );

mitkIpPicDescriptor *_mitkIpFuncHitMissI( mitkIpPicDescriptor *pic_old,
                                  mitkIpPicDescriptor *pic_masks,
                                  mitkIpFuncFlagI_t    border );

mitkIpPicDescriptor *_mitkIpFuncBorderX ( mitkIpPicDescriptor *pic_old,
                                  mitkIpUInt4_t       *edge,
                                  mitkIpFloat8_t      value );

void            _mitkIpFuncSetErrno( int error_no );

mitkIpUInt4_t _ipGetANew( mitkIpUInt4_t aNew[],  mitkIpUInt4_t Index );

mitkIpPicDescriptor *_mitkIpFuncMalloc ( mitkIpPicDescriptor *pic_old,
                                 mitkIpPicDescriptor *pic_new,  
                                 mitkIpBool_t        over_write );
#endif /* _mitkIpFuncP_h */ 
/* DON'T ADD ANYTHING AFTER THIS #endif */
