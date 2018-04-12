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

#ifndef MITKILINKEDRENDERWINDOWPART_H
#define MITKILINKEDRENDERWINDOWPART_H

#include "mitkIRenderWindowPart.h"

namespace mitk {

/**
 * \ingroup org_mitk_gui_common
 *
 * \brief Extends the IRenderWindowPart interface with methods for controlling linked
 *        render windows.
 *
 * This inteface should be implemented by subclasses of berry::IWorkbenchPart if they
 * provided several linked QmitkRenderWindow instances.
 */
struct MITK_GUI_COMMON_PLUGIN ILinkedRenderWindowPart : public virtual IRenderWindowPart {

  ~ILinkedRenderWindowPart();


  /**
   * Enable or disable the slicing planes linking the QmitkRenderWindow instances.
   *
   * \param enable <code>true</code> if the slicing planes should be enabled;
   *        <code>false</code> otherwise.
   */
  virtual void EnableSlicingPlanes(bool enable) = 0;

  /**
   * Get the enabled status of the slicing planes.
   *
   * \return <code>true</code> if the slicing planes are enabled; <code>false</code>
   *         otherwise.
   */
  virtual bool IsSlicingPlanesEnabled() const = 0;

};

}

#endif // MITKILINKEDRENDERWINDOWPART_H
