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

#ifndef TL_DOWNLOAD_H
#define TL_DOWNLOAD_H

#include <QObject>
#include <QSharedPointer>

class Download : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString percentage READ percentage)
    Q_PROPERTY(QString url        READ url)
    Q_PROPERTY(QString speed      READ speed)

public:

    Download(QString url);
    ~Download();

    QString percentage();
    QString url();
    QString speed();

private:

    QString m_url;

    qint64 m_last_interval;
    qint64 m_bytes_per_second;

    qint64 m_bytes_total;
    qint64 m_bytes_received;
};

typedef QSharedPointer<Download> DownloadPtr;

#endif // TL_DOWNLOAD_H
