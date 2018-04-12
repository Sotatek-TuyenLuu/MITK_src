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

//#include "FLmitkRenderWindow.h"
//#include "mitkOpenGLRenderer.h"
//#include <FL/x.H>
//#include <FL/Fl.h>
//void FLmitkRenderWindow::InitRenderer()
//{
//  if(m_Renderer.IsNull())
//    m_Renderer = new mitk::OpenGLRenderer;
//
//  mitk::RenderWindow::InitRenderer();
//}
//
//void FLmitkRenderWindow::draw() {
//  if(m_InitNeeded)
//  {
//    SetWindowId( (void *)fl_xid( this ) );
//    m_InitNeeded = false;
//  }
//  if(m_ResizeNeeded)
//  {
//    m_ResizeNeeded=false;
//    m_Renderer->InitSize(w(),h());
//  }
//  if(visible())
//  {
//    make_current();
//    m_Renderer->Paint();
//  }
//}
//
//
//void FLmitkRenderWindow::resize(int x, int y, int w, int h) {
//  std::cout << "resize() called" << std::endl;
//  if (visible()) {
//    m_Renderer->Resize(w,h);
//  }
//  Fl_Gl_Window::resize(x,y,w,h);
//}
