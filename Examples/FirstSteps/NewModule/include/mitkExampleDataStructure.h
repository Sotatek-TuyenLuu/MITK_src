
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

#ifndef _MITK_ExampleDataStructure_H
#define _MITK_ExampleDataStructure_H

#include <MitkNewModuleExports.h>

#include "mitkBaseData.h"

namespace mitk
{
/**
* \brief Example Data Structure
*
* This class is an example of deriving your own data structure based on mitk::BaseData .
*/
class MITKNEWMODULE_EXPORT ExampleDataStructure : public BaseData
{
public:
  // virtual methods that need to be implemented
  virtual void UpdateOutputInformation() override;
  virtual void SetRequestedRegionToLargestPossibleRegion() override;
  virtual bool RequestedRegionIsOutsideOfTheBufferedRegion() override;
  virtual bool VerifyRequestedRegion() override;
  virtual void SetRequestedRegion( const itk::DataObject* ) override;

  // Macros
  mitkClassMacro( ExampleDataStructure, BaseData );
  itkFactorylessNewMacro( Self ) itkCloneMacro( Self )

  ////////////////// Interface ///////////////////

  // Get macros
  itkGetMacro( Data, std::string );
  itkGetConstMacro( Data, std::string );

  // Set macros
  itkSetMacro( Data, std::string );

  /**
  * \brief Append a string to the data string
  *
  * Takes a string that is appended to the data string.
  *
  * \param input string to be appended
  */
  void AppendAString( const std::string input );

protected:
  ExampleDataStructure();
  virtual ~ExampleDataStructure();

  // this string is the data stored in this example data structure
  std::string m_Data;

private:
};

/**
* \brief Returns true if the example data structures are considered equal.
*
* They are considered equal if their string is equal
*/

MITKNEWMODULE_EXPORT bool Equal( mitk::ExampleDataStructure* leftHandSide,
                                 mitk::ExampleDataStructure* rightHandSide,
                                 mitk::ScalarType eps,
                                 bool verbose );

} // namespace mitk

#endif /*  _MITK_ExampleDataStructure_H */
