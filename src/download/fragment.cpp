/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "fragment.h"

Fragment::Fragment(QNetworkAccessManager *manager, const QUrl &url,
                   qint64 start, qint64 end)
    : mOffset(start)
{
    QNetworkRequest request(url);
    request.setRawHeader("Range", QString("bytes=%1-%2").arg(start).arg(end).toUtf8());
    mReply = manager->get(request);

    connect(mReply, &QNetworkReply::readyRead, this, &Fragment::onReadyRead);
    connect(mReply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &Fragment::onError);
    connect(mReply, &QNetworkReply::finished, this, &Fragment::finished);
}

void Fragment::onReadyRead()
{
    QByteArray data = mReply->readAll();
    emit dataReceived(data, mOffset);
    mOffset += data.length();
}

void Fragment::onError(QNetworkReply::NetworkError code)
{
    emit error(mReply->errorString());
}
