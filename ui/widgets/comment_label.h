// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef INSTALLER_UI_WIDGETS_COMMENT_LABEL_H
#define INSTALLER_UI_WIDGETS_COMMENT_LABEL_H

#include <QLabel>

namespace installer {

// CommentLabel displays description text below TitleLabel.
class CommentLabel : public QLabel {
  Q_OBJECT

 public:
  CommentLabel(const QString& text, QWidget* parent = nullptr);
};

}  // namespace installer

#endif  // INSTALLER_UI_WIDGETS_COMMENT_LABEL_H
