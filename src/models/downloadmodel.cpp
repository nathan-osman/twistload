/*
 * TwistLoad - a Simple Download Manager
 * Copyright (C) 2014  Nathan Osman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QSize>

#include "downloadmodel.h"

DownloadModel::DownloadModel(QObject * parent)
    : QAbstractTableModel(parent)
{
    //...
}

DownloadModel::~DownloadModel()
{
    //...
}

int DownloadModel::rowCount(const QModelIndex & parent) const
{
    return 0;
}

int DownloadModel::columnCount(const QModelIndex & parent) const
{
    return 3;
}

QVariant DownloadModel::headerData(int section, Qt::Orientation, int role) const
{
    if(role == Qt::DisplayRole)
        switch(section)
        {
            case 1: return tr("URL");
            case 2: return tr("Speed");
        }

    return QVariant();
}

QVariant DownloadModel::data(const QModelIndex & index, int role) const
{
    return QVariant();
}
