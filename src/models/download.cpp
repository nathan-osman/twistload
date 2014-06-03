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

#include <cmath>

#include "download.h"

Download::Download(QString url)
    : m_url(url),
      m_last_interval(0),
      m_bytes_per_second(256000),
      m_bytes_total(1000000),
      m_bytes_received(126000)
{
}

Download::~Download()
{
}

QString Download::percentage()
{
    if(m_bytes_total)
        return QString("%1%").arg(int((double)m_bytes_received / (double)m_bytes_total * 100.0f));
    else
        return "-";
}

QString Download::url()
{
    return m_url;
}

QString Download::speed()
{
    if(m_bytes_per_second < pow(10, 3))
        return QString("%1 B/s").arg(m_bytes_per_second);
    else if(m_bytes_per_second < pow(10, 6))
        return QString("%1 KB/s").arg(m_bytes_per_second / pow(10, 3));
    else if(m_bytes_per_second < pow(10, 9))
        return QString("%1 MB/s").arg(m_bytes_per_second / pow(10, 6));
    else
        return QString("%1 GB/s").arg(m_bytes_per_second / pow(10, 9));
}
