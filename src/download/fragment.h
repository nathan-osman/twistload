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

#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

class QNetworkAccessManager;

/**
 * @brief Individual download fragment
 *
 * Downloads consist of one or more individual fragments which download a
 * specific range of the file. As data is received, the dataReceived() signal
 * is emitted.
 */
class Fragment : public QObject
{
    Q_OBJECT

public:

    Fragment(QNetworkAccessManager *manager, const QString &url,
             qint64 start, qint64 end);
    virtual ~Fragment();

    void start();
    void stop();

Q_SIGNALS:

    void dataReceived(const QByteArray &data, qint64 offset);
    void error(const QString &message);
    void succeeded();
    void finished();

private Q_SLOTS:

    void onReadyRead();
    void onError(QNetworkReply::NetworkError code);

private:

    QNetworkAccessManager *mManager;
    QNetworkRequest mRequest;
    QNetworkReply *mReply;

    qint64 mOffset;
    qint64 mEnd;
};

#endif // FRAGMENT_H
