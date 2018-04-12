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

#include "mitkImageCropperPluginActivator.h"
#include "QmitkImageCropper.h"

namespace mitk {

void ImageCropperPluginActivator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS( QmitkImageCropper, context )
}

void ImageCropperPluginActivator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}

}
