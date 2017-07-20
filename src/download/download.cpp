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

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include "download.h"
#include "fragment.h"

Download::Download(QNetworkAccessManager *manager, const QString &url, const QString &filename)
    : mManager(manager),
      mReply(nullptr),
      mProgress(0),
      mState(Stopped),
      mUrl(url),
      mFile(filename),
      mSize(Uninitialized)
{
    init();
}

Download::Download(QNetworkAccessManager *manager, const QByteArray &json)
    : mManager(manager),
      mReply(nullptr),
      mProgress(0),
      mState(Stopped)
{
    QJsonObject object = QJsonDocument::fromJson(json).object();
    mUrl = object.value("url").toString();
    mFile.setFilename(object.value("filename").toString());
    mSize = object.value("size").toString().toLongLong();

    foreach (const QJsonValue &value, object.value("fragments").toArray()) {
        QJsonObject object = value.toObject();
        newFragment(object.value("start").toString().toLongLong(),
                    object.value("end").toString().toLongLong());
    }

    init();
}

Download::~Download()
{
    if (mReply) {
        mReply->deleteLater();
    }
    qDeleteAll(mFragments);
}

int Download::progress() const
{
    return mProgress;
}

Download::State Download::state() const
{
    return mState;
}

QString Download::url() const
{
    return mUrl;
}

QString Download::filename() const
{
    return mFile.filename();
}

qint64 Download::size() const
{
    return mSize;
}

QList<Fragment*> Download::fragments() const
{
    return mFragments;
}

QString Download::error() const
{
    return mError;
}

void Download::start()
{
    // If the file size is unknown, dispatch a request to obtain it; otherwise
    // open the file, performing allocation if necessary
    if (mSize == Uninitialized) {
        probe();
    } else {
        alloc();
    }
}

void Download::onFinished()
{
    // If the probe request succeeded, continue with allocation
    if (mReply->error() == QNetworkReply::NoError) {
        mSize = mReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
        alloc();
    } else {
        fail(mReply->errorString());
    }
}

void Download::onError(const QString &message)
{
    fail(message);
}

void Download::onAllocationProgress(int value)
{
    mProgress = value;
    emit progressChanged();
}

void Download::onAllocationSucceeded()
{
    download();
}

void Download::onDataReceived(const QByteArray &data, qint64 offset)
{
    mFile.write(data, offset);
}

void Download::init()
{
    connect(&mFile, &File::error, this, &Download::onError);
    connect(&mFile, &File::allocationProgress, this, &Download::onAllocationProgress);
    connect(&mFile, &File::allocationSucceeded, this, &Download::onAllocationSucceeded);
}

void Download::probe()
{
    mState = Probing;
    emit stateChanged();

    mReply = mManager->head(QNetworkRequest(QUrl(mUrl)));
    connect(mReply, &QNetworkReply::finished, this, &Download::onFinished);
}

void Download::alloc()
{
    mState = Allocating;
    emit stateChanged();

    mFile.open(mSize);
}

void Download::download()
{
    mState = Downloading;
    emit stateChanged();

    // TODO: set up downloads
    if (!mFragments.count()) {
        //...
    }
}

void Download::fail(const QString &message)
{
    // TODO: stop things?

    mState = Failed;
    mError = message;
    emit stateChanged();
}

Fragment *Download::newFragment(qint64 start, qint64 end)
{
    Fragment *fragment = new Fragment(mManager, mUrl, start, end);
    connect(fragment, &Fragment::dataReceived, this, &Download::onDataReceived);
    mFragments.append(fragment);
    return fragment;
}
