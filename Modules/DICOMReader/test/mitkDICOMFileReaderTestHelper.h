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

#ifndef mitkDICOMFileReaderTestHelper_h
#define mitkDICOMFileReaderTestHelper_h

#include "mitkDICOMFileReader.h"
#include "mitkDICOMEnums.h"

#include "mitkTestingMacros.h"

namespace mitk
{

class DICOMFileReaderTestHelper
{
  public:

static StringList& GetInputFilenames()
{
  static StringList inputs;
  return inputs;
}

static void SetTestInputFilenames(int argc, char* argv[])
{
  mitk::StringList inputFiles;

  for (int a = 1; a < argc; ++a)
  {
    inputFiles.push_back( argv[a] );
  }

  GetInputFilenames() = inputFiles;
}


static void SetTestInputFilenames(const StringList& filenames)
{
  GetInputFilenames() = filenames;
}

static void TestInputFilenames(DICOMFileReader* reader)
{
  StringList inputFiles = GetInputFilenames();
  reader->SetInputFiles( inputFiles );

  const StringList& inputFilesReturned = reader->GetInputFiles();
  MITK_TEST_CONDITION( inputFilesReturned.size() == inputFiles.size(), "Input file list is received")
  MITK_TEST_CONDITION( reader->GetNumberOfOutputs() == 0, "No outputs without analysis")
}

static void TestOutputsContainInputs(DICOMFileReader* reader)
{
  StringList inputFiles = GetInputFilenames();
  reader->SetInputFiles( inputFiles );

  reader->AnalyzeInputFiles();

  StringList allSortedInputsFiles;

  unsigned int numberOfOutputs = reader->GetNumberOfOutputs();
  for (unsigned int o = 0; o < numberOfOutputs; ++o)
  {
    const DICOMImageBlockDescriptor block = reader->GetOutput(o);

    const DICOMImageFrameList& outputFiles = block.GetImageFrameList();
    for(auto iter = outputFiles.cbegin();
        iter != outputFiles.cend();
        ++iter)
    {
      // check that output is part of input
      auto inputPositionOfCurrentOutput = std::find( inputFiles.cbegin(), inputFiles.cend(), (*iter)->Filename );
      if (inputPositionOfCurrentOutput !=  inputFiles.cend())
      {
        // check that output is only part of ONE output
        auto outputPositionOfCurrentOutput = std::find( allSortedInputsFiles.cbegin(), allSortedInputsFiles.cend(), (*iter)->Filename );
        if (outputPositionOfCurrentOutput == allSortedInputsFiles.cend())
        {
          // was not in list before
          allSortedInputsFiles.push_back( *inputPositionOfCurrentOutput );
        }
        else
        {
          reader->PrintOutputs(std::cout);
          MITK_TEST_CONDITION_REQUIRED(false, "File '" << (*iter)->Filename << "' appears in TWO outputs. Readers are expected to use each frame only once." )
        }
      }
      else
      {
        reader->PrintOutputs(std::cout);
        MITK_TEST_CONDITION_REQUIRED(false, "File '" << (*iter)->Filename << "' appears in output, but it was never part of the input list." )
      }
    }
  }

  MITK_TEST_CONDITION( allSortedInputsFiles.size() == inputFiles.size(), "Output list size (" << allSortedInputsFiles.size() << ") equals input list size (" << inputFiles.size() << ")" )

  try
  {
    const DICOMImageBlockDescriptor block = reader->GetOutput( inputFiles.size() );
    MITK_TEST_CONDITION(false, "Invalid indices for GetOutput() should throw exception")
  }
  catch( std::invalid_argument& )
  {
    MITK_TEST_CONDITION(true, "Invalid indices for GetOutput() should throw exception")
  }
}

static void TestMitkImagesAreLoaded( DICOMFileReader* reader,
                                     const std::unordered_map<const char*, mitk::DICOMTag>& requestedTags,
                                     const std::unordered_map<const char*, const char*>& expectedProperties )
{
  StringList inputFiles = GetInputFilenames();
  reader->SetInputFiles( inputFiles );

  reader->AnalyzeInputFiles();
  reader->LoadImages();

  unsigned int numberOfOutputs = reader->GetNumberOfOutputs();
  for (unsigned int o = 0; o < numberOfOutputs; ++o)
  {
    const DICOMImageBlockDescriptor block = reader->GetOutput(o);

    const DICOMImageFrameList& outputFiles = block.GetImageFrameList();
    const mitk::Image::Pointer mitkImage = block.GetMitkImage();
    auto iter2 = expectedProperties.cbegin();

    for ( auto iter = requestedTags.cbegin(); iter != requestedTags.cend(); ++iter, ++iter2 )
    {
      mitk::BaseProperty* property = mitkImage->GetProperty( iter->first ).GetPointer();
      MITK_TEST_CONDITION( property != nullptr,
                           "Requested Tag is available as Property in Image" );

      MITK_INFO << iter->first << " / " << property->GetNameOfClass();
    }


    MITK_DEBUG << "-------------------------------------------";
    MITK_DEBUG << "Output " << o << " at " << (void*) mitkImage.GetPointer();
    MITK_DEBUG << "  Number of files: " << outputFiles.size();
    MITK_DEBUG << "  Dimensions: " << mitkImage->GetDimension(0) << " " << mitkImage->GetDimension(1) << " " << mitkImage->GetDimension(2);
  }
}

static mitk::BaseProperty::Pointer DummyTagToPropertyFunctor( const mitk::StringLookupTable& )
{
  return mitk::BaseProperty::Pointer();
}


}; // end test class

} // namespace

#endif