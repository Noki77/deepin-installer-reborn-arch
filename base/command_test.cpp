// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "base/command.h"

#include "base/file_util.h"
#include "third_party/googletest/include/gtest/gtest.h"

namespace installer {
namespace {

TEST(CommandTest, RunScriptFile) {
  const QString script_file = "/tmp/installer-command-test.sh";
  EXPECT_TRUE(WriteTextFile(script_file, "ls /"));
  EXPECT_TRUE(RunScriptFile({script_file}));
}

TEST(CommandTest, SpawnCmd) {
  QString output;
  QString err;
  const bool ok = SpawnCmd("ls", {"-h", "/"}, output, err);
  EXPECT_TRUE(ok);
  EXPECT_GT(output.length(), 0);
  EXPECT_GT(output.indexOf("root"), 0);
}

}  // namespace
}  // namespace installer