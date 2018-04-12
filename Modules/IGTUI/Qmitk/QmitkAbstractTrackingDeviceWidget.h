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

#ifndef QmitkAbstractTrackingDeviceWidget_H
#define QmitkAbstractTrackingDeviceWidget_H

#include <QWidget>
#include "MitkIGTUIExports.h"
#include "mitkTrackingDevice.h"

#include <mitkIPersistenceService.h>

#include "QmitkTrackingDeviceConfigurationWidgetConnectionWorker.h"

//itk headers

/** Documentation:
 *  \brief Abstract class to configure a tracking device.
 *         Inherited widgets should be registered in the Microservice (TrackingDeviceCollectionWidget),
 *         If done so, they will be included in the QmitkTrackingDeviceConfigurationWidget of the Tracking Toolbox.
 *
 *         - Each implementation of this class must have a method to construct a tracking Device (ConstructTrackingDevice).
 *         - Please create the UI elements in a function like CreateQtPartControl (e.g. see QmitkVitrualTrackerWidget).
 *         - You might want to use own buttons etc., please connect them in a private CreateConnections (e.g. see QmitkVitrualTrackerWidget).
 *         - Due to initialization of qt during autoloading of the IGT module, you constructor should be as slim as possible and only contain a call
 *           of the QmitkAbstractTrackingDeviceWidget constructor and simple variable initialization.
 *         - For the initialization, you must write an Iniltialize() function, which must include a call of InitializeSuperclassWidget() and should contain
 *           calls of your private CreateConnections / CreateQtPartControl (if you implemented these).
 *         - For integration into the TrackingToolbox, a clone function is needed. Here, a new widget should be created, Initialize() needs to be called,
 *           and all settings of your widget should be copied.
 *
 *         You can Load and Store previous settings of your GUI elements (e.g. see QmitkNDIPolarisWidget).
 *         Also, you can add an output textbox to your widget to display information about your device status. It's optional, see e.g. QmitkNDIAuroraWidget.
 *         Some Devices need the information if drivers are installed on your computer. If this is necessary for your device to avoid crashes,
 *         please override IsDeviceInstalled. The default return value is true otherwise.
 *
 *  \ingroup IGTUI
 */
class MITKIGTUI_EXPORT QmitkAbstractTrackingDeviceWidget : public QWidget
{
  Q_OBJECT

public:
  static const std::string VIEW_ID;

  QmitkAbstractTrackingDeviceWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

  virtual ~QmitkAbstractTrackingDeviceWidget();

  /**
   * \brief Return pointer to copy of the object.
   * Internally use of QmitkUSAbstractCustomWidget::Clone() with additionaly
   * setting an internal flag that the object was really cloned.
   */
  QmitkAbstractTrackingDeviceWidget* CloneForQt(QWidget* parent = 0) const;

  /**
  * \brief Subclass must implement this method to return a pointer to a copy of the object.
  * Please don't forget to call InitializeSuperclassWidget(), CreateQtPartControl and optionally CreateConnections during this function.
  */
  virtual void Initialize() = 0;

  bool IsInitialized() const { return isInitialized; }

signals:
  void ConnectionTested(bool connected, QString output);

  protected slots:
  void TestConnectionFinished(bool connected, QString output);

  /* @brief This method is called when the user presses the button "test connection". The method will then create a temporary tracking device,
   *        try to open a connection and start tracking. The user can see the result of the connection test on the small output window.
   */
  void TestConnection();

private:
  /// \brief Creation of the connections. You might implement the same function again in your inherited widget.
  void CreateConnections();

protected:
  PERSISTENCE_GET_SERVICE_METHOD_MACRO
    void InitializeSuperclassWidget();

  QmitkTrackingDeviceConfigurationWidgetConnectionWorker* m_TestConnectionWorker;
  QThread* m_TestConnectionWorkerThread;

  /**
   * \brief Subclass must implement this method to return a pointer to a copy of the object.
   * Please don't forget to call Initialize() during this function and copy all of your settings.
   */
  virtual QmitkAbstractTrackingDeviceWidget* Clone(QWidget* parent = 0) const = 0;

public:
  /**
  * \brief Optional method to add output to a small screen in the trackingToolbox (see QmitkNDIPolarisWidget)
  */
  virtual void ResetOutput() {}
  /**
  * \brief Optional method to add output to a small screen in the trackingToolbox (see QmitkNDIPolarisWidget)
  */
  virtual void AddOutput(std::string) {}
  virtual mitk::TrackingDevice::Pointer ConstructTrackingDevice() = 0;

  /**
  * \brief Optional method to store and load settings of your widget (see QmitkNDIPolarisWidget)
  */
  virtual void StoreUISettings() {}

  /**
  * \brief Optional method to store and load settings of your widget (see QmitkNDIPolarisWidget)
  */
  virtual void LoadUISettings() {}

  /**
  * \brief Optional method to investigate if drivers etc for your device are installed.
  * The default value is "true" as most devices don't need this information.
  * Others however migth crash, and for these you might implement this function (see QmitkMicronTrackerWidget)
  */
  virtual bool IsDeviceInstalled() { return true; }

  std::string m_ErrorMessage; ///< current problem description

private:
  /**
  * \warning Don't touch this variable if you don't know what you are doing!
  */
  bool isInitialized;
};

#endif
