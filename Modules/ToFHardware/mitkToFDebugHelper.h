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
#include <mitkImageToOpenCVImageFilter.h>
//#include <mitkImage.h

namespace mitk
{
  class ToFDebugHelper
  {
  public:

    inline static void ToFDebugHelper::ShowCVDistanceImage(float* distances, unsigned int dimX, unsigned int dimY)
    {
      unsigned int* dim = new unsigned int[2];
      dim[0] = dimX;
      dim[1] = dimY;
      mitk::Image::Pointer image = mitk::Image::New();
      image->Initialize(mitk::PixelType(mitk::MakeScalarPixelType<float>()), 2, dim);
      image->SetSlice(distances);

      mitk::ImageToOpenCVImageFilter::Pointer filter = mitk::ImageToOpenCVImageFilter::New();
      filter->SetImage(image);
      cv::Mat cvImage = cv::Mat(filter->GetOpenCVImage(), true);
      double minVal, maxVal;
      cv::minMaxLoc(cvImage, &minVal, &maxVal);
      cv::Mat uCCImage;
      cvImage.convertTo(uCCImage, CV_8U, 255.0/(maxVal - minVal), -minVal);
      cv::namedWindow("Debug Image", CV_WINDOW_AUTOSIZE);
      cv::imshow("Debug Image", uCCImage);
      cv::waitKey(10000000);
    }
  };
}
