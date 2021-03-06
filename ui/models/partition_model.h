// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_UI_MODELS_PARTITION_MODEL_H
#define INSTALLER_UI_MODELS_PARTITION_MODEL_H

#include <QList>
#include <QObject>
class QThread;

#include "partman/device.h"
#include "partman/operation.h"

namespace installer {

class PartitionManager;

// Communication with partman/PartitionManager.
// Both SimplePartitionDelegate and AdvancedPartitionDelegate read real device
// list and send operation list to this class.
class PartitionModel : public QObject {
  Q_OBJECT

 public:
  explicit PartitionModel(QObject* parent = nullptr);
  ~PartitionModel();

 signals:
  // Emitted when auto partitioning job is done.
  void autoPartDone(bool ok);

  // Emitted after scanning local disk devices.
  void deviceRefreshed(const DeviceList& devices);

  // Emitted when manual partitioning job is done.
  // See PartitionManager about |real_operations|.
  void manualPartDone(bool ok, const OperationList& real_operations);

 public slots:
  // Notify PartitionManager to do auto-part
  void autoPart();

  // Create partition table at |device_path| to match current booting method.
  // After that, emit deviceRefreshed() signal.
  void createPartitionTable(const QString& device_path);

  // Do manual partitioning based on these |operations|.
  void manualPart(const OperationList& operations);

  // Notifies partition manager to scan devices.
  void scanDevices();

 private:
  void initConnections();

  PartitionManager* partition_manager_ = nullptr;
  QThread* partition_thread_ = nullptr;
};

}  // namespace installer

#endif  // INSTALLER_UI_MODELS_PARTITION_MODEL_H
