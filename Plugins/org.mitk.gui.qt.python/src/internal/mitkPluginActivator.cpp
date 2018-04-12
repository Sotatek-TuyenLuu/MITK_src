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

#include "mitkPluginActivator.h"
#include "QmitkPythonView.h"

namespace mitk
{
    QString PluginActivator::m_XmlFilePath;

    void PluginActivator::start(ctkPluginContext* context)
    {
      m_XmlFilePath = context->getDataFile("PythonSnippets.xml").absoluteFilePath();

      BERRY_REGISTER_EXTENSION_CLASS(QmitkPythonView, context)
    }

    void PluginActivator::stop(ctkPluginContext* context)
    {
        Q_UNUSED(context)
    }
}
