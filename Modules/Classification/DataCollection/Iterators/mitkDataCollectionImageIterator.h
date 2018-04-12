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


#ifndef mitkDataCollectionImageIterator_H
#define mitkDataCollectionImageIterator_H


#include <mitkDataCollection.h>
#include <itkImageRegionIterator.h>

/**
  \brief Follow Up Storage - Class to facilitate loading/accessing structured follow-up data

  Data is into a collection that may contain further (sub) collections or images.
*/

namespace mitk
{
  template <typename TDataType, int ImageDimension>
  class DataCollectionImageIterator
  {
  public:
    typedef itk::Image<TDataType, ImageDimension> ImageType;
    typedef typename ImageType::Pointer ImagePointerType;
    typedef itk::ImageRegionIterator<ImageType> ImageIterator;

    DataCollectionImageIterator(DataCollection::Pointer collection, std::string imageName);

    void ToBegin();

    bool IsAtEnd();

    void operator++();

    // TODO refactor implementation
    void operator++(int);

    TDataType GetVoxel();

    void SetVoxel(TDataType value);

    size_t GetIndex();
    size_t GetImageIndex () { return m_ImageIndex;}

    std::string GetFilePrefix();

    void NextObject();

    ImageIterator GetImageIterator();

  private:
    DataCollectionImageIterator<TDataType, ImageDimension>* GetNextDataCollectionIterator(size_t start);

    // DATA
    DataCollection::Pointer m_Collection;
    std::string m_ImageName;

    bool m_IsAtEnd;
    bool m_IteratingImages;
    size_t m_CurrentIndex;
    size_t m_ImageIndex;

    size_t m_CurrentElement;
    DataCollectionImageIterator<TDataType, ImageDimension>* m_CurrentCollectionIterator;
    ImageIterator m_CurrentIterator;
  };
} // end namespace

#include <Iterators/mitkDataCollectionImageIterator.cxx>
#endif //mitkDataCollectionImageIterator_H
