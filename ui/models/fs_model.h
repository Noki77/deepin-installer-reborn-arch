// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_UI_MODELS_FS_MODEL_H
#define INSTALLER_UI_MODELS_FS_MODEL_H

#include <QAbstractListModel>

#include "partman/fs.h"

namespace installer {

class FsModel : public QAbstractListModel {
  Q_OBJECT

 public:
  FsModel(const FsTypeList& fs_list, QObject* parent = nullptr);

  QVariant data(const QModelIndex& index, int role) const override;
  int rowCount(const QModelIndex& parent) const override;

  // Get fs type at |index|.
  FsType getFs(int index) const;

  // Index fs type. Returns -1 if not found.
  int index(FsType fs_type) const;

  // If |show_efi| is false, remove efi from fs list.
  void setShowEFI(bool show_efi);

  // If |show_unknown| is true, append it to fs list.
  void setShowUnknown(bool show_unknown);

 private:
  FsTypeList fs_list_;
};

}  // namespace installer

#endif  // INSTALLER_UI_MODELS_FS_MODEL_H
