set(CPP_FILES
  mitkImageRegistrationMethod.cpp
  mitkMetricParameters.cpp
  mitkOptimizerFactory.cpp
  mitkOptimizerParameters.cpp
  mitkRigidRegistrationObserver.cpp
  mitkRigidRegistrationPreset.cpp
  mitkTransformParameters.cpp
  mitkPyramidalRegistrationMethod.cpp
)

set(RESOURCE_FILES
  mitkRigidRegistrationPresets.xml
  mitkRigidRegistrationTestPresets.xml
)

MITK_MULTIPLEX_PICTYPE( mitkImageRegistrationMethod-TYPE.cpp )
MITK_MULTIPLEX_PICTYPE( mitkPyramidalRegistrationMethod-TYPE.cpp )
