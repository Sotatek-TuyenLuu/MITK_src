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

#include "mitkRigidRegistrationTestPreset.h"
#include <itkArray.h>

int mitkRigidRegistrationTestPresetTest(int /*argc*/, char* /*argv*/[])
{
  typedef itk::Array<double>               ArrayType;

  mitk::RigidRegistrationTestPreset* rrp = new mitk::RigidRegistrationTestPreset;
  std::cout<<"[PASSED]"<<std::endl;

  // Check if the default presets (in the Functionality directory) can be loaded.
  std::cout<<"Testing default parameter loading...\n";
  if(!rrp->LoadPreset())
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  // Check if an exemplary parameter set can be extracted from the read presets.
  std::cout<<"Testing if exemplary default values match default parameters...\n";

  ArrayType transformValues = rrp->getTransformValues("ITK Image Registration 12");
  ArrayType metricValues = rrp->getMetricValues("ITK Image Registration 12");
  ArrayType optimizerValues = rrp->getOptimizerValues("ITK Image Registration 12");
  ArrayType interpolatorValues = rrp->getInterpolatorValues("ITK Image Registration 12");

  std::cout << transformValues[5] << metricValues[1] << optimizerValues[4] << interpolatorValues[0] << std::endl;

  if( !(transformValues[5]==0.001) || !(metricValues[1]==1) || !(optimizerValues[4]==0.1) || !(interpolatorValues[0]==0) )
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  // Testing if a save operation can be performed.
  std::cout<<"Testing if saving is possible...\n";
  if (!rrp->newPresets( rrp->getTransformValuesPresets(), rrp->getMetricValuesPresets(),
    rrp->getOptimizerValuesPresets(), rrp->getInterpolatorValuesPresets(), "TestPresets.xml" ))
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  // Testing what happens if we now repeat the test with the previously written xml file
  delete rrp;

  mitk::RigidRegistrationTestPreset* rrp2 = new mitk::RigidRegistrationTestPreset;
  std::cout<<"[PASSED]"<<std::endl;

  // Check if the default presets (in the Functionality directory) can be loaded.
  std::cout<<"Testing default parameter loading, second time...\n";
  if(!rrp2->LoadPreset("TestPresets.xml"))
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  // Check if an exemplary parameter set can be extracted from the read presets.
  std::cout<<"Testing if exemplary default values match default parameters, second time...\n";

  transformValues = rrp2->getTransformValues("ITK Image Registration 12");
  metricValues = rrp2->getMetricValues("ITK Image Registration 12");
  optimizerValues = rrp2->getOptimizerValues("ITK Image Registration 12");
  interpolatorValues = rrp2->getInterpolatorValues("ITK Image Registration 12");

  if( !(transformValues[5]==0.001) || !(metricValues[1]==1) || !(optimizerValues[4]==0.1) || !(interpolatorValues[0]==0) )
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  delete rrp2;

  std::cout<<"[TEST DONE]"<<std::endl;
  return EXIT_SUCCESS;
}
