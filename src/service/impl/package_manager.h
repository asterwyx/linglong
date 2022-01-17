/*
 * Copyright (c) 2020-2021. Uniontech Software Ltd. All rights reserved.
 *
 * Author:     Iceyer <me@iceyer.net>
 *
 * Maintainer: Iceyer <me@iceyer.net>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QDBusArgument>
#include <QDBusContext>
#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <DSingleton>

#include "json_register_inc.h"
#include "module/package/package.h"
#include "module/runtime/container.h"
#include "module/util/package_manager_param.h"
#include "module/util/singleton.h"
#include "package_manager_impl.h"
#include "qdbus_retmsg.h"

#include "package_manager_flatpak_impl.h"

using linglong::service::util::AppInstance;

class PackageManagerPrivate;
class PackageManager : public QObject
    , protected QDBusContext
    , public Dtk::Core::DSingleton<PackageManager>
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.linglong.PackageManager")

    friend class Dtk::Core::DSingleton<PackageManager>;

public Q_SLOTS:
    QString Status();

    RetMessageList Download(const QStringList &packageIdList, const QString savePath);
    RetMessageList Install(const QStringList &packageIdList, const ParamStringMap &paramMap = {});
    RetMessageList Uninstall(const QStringList &packageIdList, const ParamStringMap &paramMap = {});
    QString Update(const QStringList &packageIdList);
    QString UpdateAll();

    AppMetaInfoList Query(const QStringList &packageIdList, const ParamStringMap &paramMap = {});

    QString Import(const QStringList &packagePathList);

    RetMessageList Start(const QString &packageId, const ParamStringMap &paramMap = {});
    RetMessageList Stop(const QString &containerId);
    ContainerList ListContainer();

private:
    QScopedPointer<PackageManagerPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(dd_ptr), PackageManager)

protected:
    PackageManager();
    ~PackageManager() override;
};