// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "partman/utils.h"

#include <parted/parted.h>
#include <string.h>
#include <QDebug>
#include <QDir>

#include "partman/structs.h"
#include "sysinfo/proc_partitions.h"

namespace installer {

qint64 GetMaximumDeviceSize() {
  const PartitionItemList list = ParsePartitionItems();
  qint64 result = 0;
  for (const PartitionItem item : list) {
    result = qMax(result, item.blocks);
  }

  // Convert kib to bytes.
  return result * kKibiByte;
}

PartitionTableType GetPrimaryDiskPartitionTable() {
  // TODO(xushaohua): Read path to the first device.
  PedDevice* device = ped_device_get("/dev/sda");
  if (device == NULL) {
    return PartitionTableType::Unknown;
  }
  PedDiskType* disk_type = ped_disk_probe(device);
  if (disk_type == NULL) {
    return PartitionTableType::Empty;
  }

  const QString disk_type_name(disk_type->name);
  if (disk_type_name == kPartitionTableMsDos) {
    return PartitionTableType::MsDos;
  } else if (disk_type_name == kPartitionTableGPT) {
    return PartitionTableType::GPT;
  }

  return PartitionTableType::Others;
}

}  // namespace installer