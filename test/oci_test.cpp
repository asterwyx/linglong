/*
 * Copyright (c) 2020-2021. Uniontech Software Ltd. All rights reserved.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include "box/util/oci-runtime.h"

TEST(OCI, Runtime)
{
    auto r = linglong::fromFile("../../test/data/demo/config-mini.json");

    EXPECT_EQ(r.version, "1.0.1");
    EXPECT_EQ(r.process.args[0], "/bin/bash");
    EXPECT_EQ(r.process.env[1], "TERM=xterm");
    EXPECT_EQ(r.mounts.at(1).options.at(1), "strictatime");
    EXPECT_EQ(r.linux.namespaces.size(), 4);

    EXPECT_EQ(r.linux.uidMappings.size(), 2);
    EXPECT_EQ(r.linux.uidMappings.at(1).hostID, 1000);
    EXPECT_EQ(r.linux.uidMappings.at(1).containerID, 1000);
    EXPECT_EQ(r.linux.uidMappings.at(1).size, 1);

    EXPECT_EQ(r.linux.gidMappings.size(), 2);
    EXPECT_EQ(r.linux.gidMappings.at(0).hostID, 65534);
    EXPECT_EQ(r.linux.gidMappings.at(0).containerID, 0);
    EXPECT_EQ(r.linux.gidMappings.at(0).size, 1);
}

TEST(OCI, Util)
{
    EXPECT_EQ(util::format("%d %d %d\n", 1, 1, 1), "1 1 1\n");
    EXPECT_EQ(util::format("%d %d %d\n", uint64_t(1), 1u, 1), "1 1 1\n");
}