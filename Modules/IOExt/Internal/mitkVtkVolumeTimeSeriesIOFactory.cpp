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

#include "mitkVtkVolumeTimeSeriesIOFactory.h"
#include "mitkIOAdapter.h"
#include "mitkVtkVolumeTimeSeriesReader.h"

#include "itkVersion.h"


namespace mitk
{
VtkVolumeTimeSeriesIOFactory::VtkVolumeTimeSeriesIOFactory()
{
  this->RegisterOverride("mitkIOAdapter",
                         "mitkVtkVolumeTimeSeriesReader",
                         "mitk Vtk Surface IO",
                         1,
                         itk::CreateObjectFunction<IOAdapter<VtkVolumeTimeSeriesReader> >::New());
}

VtkVolumeTimeSeriesIOFactory::~VtkVolumeTimeSeriesIOFactory()
{
}

const char* VtkVolumeTimeSeriesIOFactory::GetITKSourceVersion() const
{
  return ITK_SOURCE_VERSION;
}

const char* VtkVolumeTimeSeriesIOFactory::GetDescription() const
{
  return "VtkVolumeTimeSeries IO Factory, allows the loading of Vtk surfaces";
}

} // end namespace mitk
