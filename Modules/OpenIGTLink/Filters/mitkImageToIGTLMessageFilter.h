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

#ifndef _MITKIMAGEToIGTLMessageFILTER_H__
#define _MITKIMAGEToIGTLMessageFILTER_H__

#include <mitkCommon.h>
#include <mitkIGTLMessageSource.h>
#include <mitkImage.h>
#include <mitkImageSource.h>

namespace mitk
{
/**Documentation
 *
 * \brief This filter creates IGTL messages from mitk::Image objects
 *
 * \ingroup OpenIGTLink
 *
 */
class MITKOPENIGTLINK_EXPORT ImageToIGTLMessageFilter : public IGTLMessageSource
{
 public:
  mitkClassMacro(ImageToIGTLMessageFilter, IGTLMessageSource);
  itkFactorylessNewMacro(Self);
  itkCloneMacro(Self);

  /**
   * \brief filter execute method
   */
  virtual void GenerateData() override;

  using Superclass::SetInput;

  /**
   * \brief Sets one input Image
   */
  virtual void SetInput(const mitk::Image* img);

  /**
   * \brief Sets the input Image at a specific index
   */
  virtual void SetInput(unsigned int idx, const Image* img);

  /**
  * \brief Returns the input of this filter
  */
  const mitk::Image* GetInput();

  /**
   * \brief Returns the input of this filter
   */
  const mitk::Image* GetInput(unsigned int idx);

  /**
  * empty implementation to prevent calling of the superclass method that
  * would try to copy information from the input Image to the output
  * PointSet, which makes no sense!
  */
  virtual void GenerateOutputInformation() override{};

  /**
   * \brief Connects the input of this filter to the outputs of the given
*ImageSource
   *
* This method does not support smartpointer. use FilterX.GetPointer() to
* retrieve a dumbpointer.
   */
  virtual void ConnectTo(mitk::ImageSource* UpstreamFilter);

 protected:
  ImageToIGTLMessageFilter();

  virtual ~ImageToIGTLMessageFilter() {};

  /**
  * \brief create output objects for all inputs
  */
  virtual void CreateOutputsForAllInputs();

  mitk::ImageSource* m_Upstream;
};
}  // namespace mitk

#endif  // _MITKIMAGEToIGTLMessageFILTER_H__
