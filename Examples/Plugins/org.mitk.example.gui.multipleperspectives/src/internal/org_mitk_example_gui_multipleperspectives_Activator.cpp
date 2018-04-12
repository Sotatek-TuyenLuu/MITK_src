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


#include "org_mitk_example_gui_multipleperspectives_Activator.h"

#include "MultiplePerspectives.h"
#include "MinimalPerspective.h"
#include "ExtendedPerspective.h"
#include "EmptyView1.h"
#include "EmptyView2.h"

void org_mitk_example_gui_multipleperspectives_Activator::start(ctkPluginContext* context)
{
  BERRY_REGISTER_EXTENSION_CLASS(MultiplePerspectives, context)
  BERRY_REGISTER_EXTENSION_CLASS(MinimalPerspective, context)
  BERRY_REGISTER_EXTENSION_CLASS(ExtendedPerspective, context)
  BERRY_REGISTER_EXTENSION_CLASS(EmptyView1, context)
  BERRY_REGISTER_EXTENSION_CLASS(EmptyView2, context)
}

void org_mitk_example_gui_multipleperspectives_Activator::stop(ctkPluginContext* context)
{
  Q_UNUSED(context)
}
