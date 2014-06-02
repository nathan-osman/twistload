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

#ifndef TL_DOWNLOADMODEL_H
#define TL_DOWNLOADMODEL_H

#include <QAbstractTableModel>

class DownloadModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit DownloadModel(QObject * parent = 0);
    ~DownloadModel();

    int rowCount(const QModelIndex & parent) const;
    int columnCount(const QModelIndex & parent) const;

    QVariant headerData(int section, Qt::Orientation, int role) const;
    QVariant data(const QModelIndex & index, int role) const;
};

#endif // TL_DOWNLOADMODEL_H
