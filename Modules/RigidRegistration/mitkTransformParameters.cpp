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


#include "mitkTransformParameters.h"


namespace mitk {

  TransformParameters::TransformParameters() :
    m_Transform(TRANSLATIONTRANSFORM),
    m_Angle(0.0),
    m_Scale(1.0),
    m_TransformInitializerOn(true),
    m_MomentsOn(true),
    m_UseOptimizerScales(true),
    m_TransformCenterX(0.0),
    m_TransformCenterY(0.0),
    m_TransformCenterZ(0.0)
    {
      m_InitialParameters.set_size(0);
      m_Scales.SetSize(16);
      m_Scales.Fill(1.0);
    }

  void TransformParameters::SetScales(itk::Array<double> scales)
  {
    m_Scales = scales;
  }

  itk::Array<double> TransformParameters::GetScales()
  {
    return m_Scales;
  }

  void TransformParameters::SetInitialParameters(itk::Array<double> initialParameters)
  {
    m_InitialParameters = initialParameters;
  }

  itk::Array<double> TransformParameters::GetInitialParameters()
  {
    return m_InitialParameters;
  }
} // namespace mitk
