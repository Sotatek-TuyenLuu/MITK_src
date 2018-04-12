/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center, 
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without 
even the implied warranty of MERCHANTABILITY or FITNESS FOR 
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/
#ifndef IPSEGMENTATIONP_H
#define IPSEGMENTATIONP_H

#include <mitkIpPic.h>
#include "ipSegmentationError.h"

#ifndef IPSEGMENTATION_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

#define ipMITKSegmentationTYPE mitkIpUInt1_t
#define ipMITKSegmentationTYPE_ID mitkIpPicUInt
#define ipMITKSegmentationBPE 8
#define tagSEGMENTATION_EMPTY "SEGMENTATION_EMPTY"

enum LogicalOp {
    IPSEGMENTATION_OP  /*! copy of input image */,
    IPSEGMENTATION_AND   /*! logical and operator */,
    IPSEGMENTATION_OR  /*! the or operator */,
    IPSEGMENTATION_XOR  /*! the exclusive-or operator */
};

extern void ipMITKSegmentationUndoSave (mitkIpPicDescriptor* segmentation);
extern mitkIpBool_t ipMITKSegmentationUndoIsEnabled (mitkIpPicDescriptor* segmentation);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* IPSEGMTATION_H */

#define AND(TYPE, PIC, VALUE, X, Y)                                       \
{                                                                         \
  TYPE* data = (TYPE*) (PIC)->data;                                       \
  mitkIpUInt4_t  width = (PIC)->n[0];                                         \
  int temp =  (int) data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X];        \
  temp &= (int) VALUE;                                                    \
  data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X] = temp;                   \
}                                                                         \

#define OR(TYPE, PIC, VALUE, X, Y)                                        \
{                                                                         \
  TYPE* data = (TYPE*) (PIC)->data;                                       \
   mitkIpUInt4_t  width = (PIC)->n[0];                                        \
  int temp =  (int) data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X];        \
  temp |= (int) VALUE;                                                    \
   data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X]  = temp;                 \
}                                                                         \

#define  XOR(TYPE, PIC, VALUE, X, Y)                                      \
{                                                                         \
  TYPE* data = (TYPE*) (PIC)->data;                                       \
  mitkIpUInt4_t width = (PIC)->n[0];                                          \
  int temp =  (int) data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X];        \
  temp ^= (int) VALUE;                                                    \
  data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X]  = temp;                  \
}                                                                         \

#define OP(TYPE, PIC, VALUE, X, Y)                                        \
{                                                                         \
  TYPE* data = (TYPE*) (PIC)->data;                                       \
  mitkIpUInt4_t width = (PIC)->n[0];                                          \
  data [width * (mitkIpUInt4_t) Y + (mitkIpUInt4_t)  X] = VALUE;                  \
}                                                                         \

#define MASK(TYPE, PIC, MSK, VALUE, X, Y, CMD)          \
{                    \
if (!(MSK) || (((ipMITKSegmentationTYPE *)(MSK)->data)[(PIC)->n[0] * (mitkIpUInt4_t) (Y) + (mitkIpUInt4_t)  (X)] > 0.0)) \
CMD(TYPE, PIC, VALUE, X, Y)              \
}

#endif
