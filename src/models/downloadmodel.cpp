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

#include <QPair>
#include <QSize>

#include "downloadmodel.h"

const char * columns[][2] = {
    {"percentage", ""},
    {"url",        "URL"},
    {"speed",      "Speed"}
};

DownloadModel::DownloadModel(QObject * parent)
    : QAbstractTableModel(parent)
{
    downloads.append(QSharedPointer<Download>(new Download));
}

DownloadModel::~DownloadModel()
{
    //...
}

int DownloadModel::rowCount(const QModelIndex & parent) const
{
    return parent.isValid() ? 0 : downloads.count();
}

int DownloadModel::columnCount(const QModelIndex & parent) const
{
    return parent.isValid() ? 0 : sizeof(columns) / sizeof(QString) / 2;
}

QVariant DownloadModel::headerData(int section, Qt::Orientation, int role) const
{
    if(role == Qt::DisplayRole)
        return columns[section][1];

    return QVariant();
}

QVariant DownloadModel::data(const QModelIndex & index, int role) const
{
    if(role == Qt::DisplayRole)
        return downloads[index.row()]->property(columns[index.column()][0]);

    return QVariant();
}
