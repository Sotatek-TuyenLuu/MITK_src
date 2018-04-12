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

#ifndef __itkTotalVariationDenoisingImageFilter_h
#define __itkTotalVariationDenoisingImageFilter_h

#include "itkTotalVariationSingleIterationImageFilter.h"
#include "itkImageToImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkImage.h"

namespace itk
{
/** \class TotalVariationDenoisingImageFilter
 * \brief Applies a total variation denoising filter to an image
 *
 * Reference: Tony F. Chan et al., The digital TV filter and nonlinear denoising
 *
 * \sa Image
 * \sa Neighborhood
 * \sa NeighborhoodOperator
 * \sa NeighborhoodIterator
 *
 * \ingroup IntensityImageFilters
 */
template <class TInputImage, class TOutputImage>
class TotalVariationDenoisingImageFilter :
    public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Extract dimension from input and output image. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Convenient typedefs for simplifying declarations. */
  typedef TInputImage InputImageType;
  typedef TOutputImage OutputImageType;

  /** Standard class typedefs. */
  typedef TotalVariationDenoisingImageFilter Self;
  typedef ImageToImageFilter< InputImageType, OutputImageType> Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkFactorylessNewMacro(Self)
  itkCloneMacro(Self)

  /** Run-time type information (and related methods). */
  itkTypeMacro(TotalVariationDenoisingImageFilter, ImageToImageFilter);

  /** Image typedef support. */
  typedef typename InputImageType::PixelType InputPixelType;
  typedef typename OutputImageType::PixelType OutputPixelType;

  typedef typename InputImageType::RegionType InputImageRegionType;
  typedef typename OutputImageType::RegionType OutputImageRegionType;

  typedef typename InputImageType::SizeType InputSizeType;

  typedef TotalVariationSingleIterationImageFilter<TOutputImage, TOutputImage>
    SingleIterationFilterType;

  typedef typename itk::CastImageFilter< TInputImage, TOutputImage > CastType;

  itkSetMacro(Lambda, double);
  itkGetMacro(Lambda, double);

  itkSetMacro(NumberIterations, int);
  itkGetMacro(NumberIterations, int);

protected:
  TotalVariationDenoisingImageFilter();
  virtual ~TotalVariationDenoisingImageFilter() {}
  void PrintSelf(std::ostream& os, Indent indent) const;

  void GenerateData();

  double m_Lambda;

  int m_NumberIterations;

private:
  TotalVariationDenoisingImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkTotalVariationDenoisingImageFilter.txx"
#endif

#endif //__itkTotalVariationDenoisingImageFilter__
