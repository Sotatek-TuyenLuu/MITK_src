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

#ifndef MITKIGTLMessageToUSImageFilter_H_HEADER_INCLUDED_
#define MITKIGTLMessageToUSImageFilter_H_HEADER_INCLUDED_

#include <mitkCommon.h>
#include <MitkUSExports.h>
#include <mitkUSImageSource.h>
#include <mitkIGTLMessageSource.h>
#include <igtlImageMessage.h>

namespace mitk
{
  class MITKUS_EXPORT IGTLMessageToUSImageFilter : public USImageSource
  {
  public:
    mitkClassMacro(IGTLMessageToUSImageFilter, USImageSource);
    itkFactorylessNewMacro(Self);
    itkCloneMacro(Self);

    /**
    *\brief Sets the number of expected outputs.
    *
    * Normally, this is done automatically by the filter concept. However, in our
    * case we can not know, for example, how many tracking elements are stored
    * in the incoming igtl message. Therefore, we have to set the number here to
    * the expected value.
    */
    void SetNumberOfExpectedOutputs(unsigned int numOutputs);

    /**
    *\brief Connects the input of this filter to the outputs of the given
    * IGTLMessageSource
    *
    * This method does not support smartpointer. use FilterX.GetPointer() to
    * retrieve a dumbpointer.
    */
    void ConnectTo(mitk::IGTLMessageSource* UpstreamFilter);

  protected:
    IGTLMessageToUSImageFilter();

    using Superclass::GetNextRawImage;

    /**
     * \brief Copies the data from the next OIGTL message to an mitk::Image.
     *
     * \param img the image to fill with the data from the OIGTL message.
     */
    virtual void GetNextRawImage(mitk::Image::Pointer& img);

  private:
    mitk::IGTLMessageSource* m_upstream;
    mitk::Image::Pointer m_previousImage;
    /**
     * \brief Templated method to copy the data of the OIGTL message to the image, depending
     * on the pixel type contained in the message.
     *
     * \param img the image to fill with the data from msg
     * \param msg the OIGTL message to copy the data from
     * \param big_endian whether the data is in big endian byte order
     */
    template <typename TPixel>
    void Initiate(mitk::Image::Pointer& img, igtl::ImageMessage* msg, bool big_endian);
  };
}  // namespace mitk

#endif  // MITKIGTLMessageToUSImageFilter_H_HEADER_INCLUDED_
