// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/frames/inner/system_info_timezone_frame.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCore/QEvent>

#include "service/settings_manager.h"
#include "service/settings_name.h"
#include "sysinfo/timezone.h"
#include "ui/frames/consts.h"
#include "ui/widgets/comment_label.h"
#include "ui/widgets/nav_button.h"
#include "ui/widgets/title_label.h"

namespace installer {

namespace {

const char kTextTitle[] = "Select Time Zone";
const char kTextComment[] = "Mark your zone in the map";
const char kTextBack[] = "Back";

}  // namespace

SystemInfoTimezoneFrame::SystemInfoTimezoneFrame(QWidget* parent)
    : QFrame(parent),
      timezone_(GetSettingsString(kSystemInfoDefaultTimezone)) {
  this->setObjectName("system_info_timezone_frame");

  if (!IsValidTimezone(timezone_)) {
    timezone_ = GetCurrentTimezone();
  }
  this->initUI();
  this->initConnections();
}

void SystemInfoTimezoneFrame::autoConf() {
  if (IsValidTimezone(timezone_)) {
    WriteTimezone(timezone_);
    emit this->timezoneUpdated(GetTimezoneName(timezone_));
  } else {
    qWarning() << "autoConf() got invalid timezone:" << timezone_;
  }
}

void SystemInfoTimezoneFrame::changeEvent(QEvent* event) {
  if (event->type() == QEvent::LanguageChange) {
    title_label_->setText(tr(kTextTitle));
    comment_label_->setText(tr(kTextComment));
    back_button_->setText(tr(kTextBack));
  } else {
    QFrame::changeEvent(event);
  }
}

void SystemInfoTimezoneFrame::initConnections() {
  connect(back_button_, &QPushButton::clicked,
          this, &SystemInfoTimezoneFrame::finished);
}

void SystemInfoTimezoneFrame::initUI() {
  title_label_ = new TitleLabel(tr(kTextTitle));
  comment_label_ = new CommentLabel(tr(kTextComment));
  back_button_ = new NavButton(tr(kTextBack));

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(kMainLayoutSpacing);
  layout->addStretch();
  layout->addWidget(title_label_, 0, Qt::AlignCenter);
  layout->addWidget(comment_label_, 0, Qt::AlignCenter);
  layout->addStretch();
  layout->addWidget(back_button_, 0, Qt::AlignCenter);

  this->setLayout(layout);
}

}  // namespace installer