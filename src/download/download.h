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

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QList>
#include <QObject>

#include "../fs/file.h"

class QNetworkAccessManager;
class QNetworkReply;

class Fragment;

/**
 * @brief Download for an individual file
 *
 * Downloads may be broken into fragments to increase throughput.
 */
class Download : public QObject
{
    Q_OBJECT

public:

    enum {
        /// Download probe has not yet been completed
        Uninitialized = -1,
        /// Download size was not provided
        Unknown = 0
    };

    enum State {
        /// Download is stopped
        Stopped,
        /// Download metadata is being retrieved
        Probing,
        /// Space is being allocated on disk
        Allocating,
        /// File is being downloaded
        Downloading,
        /// An error has occurred
        Failed
    };

    /**
     * @brief Create a new download
     * @param manager network access manager
     * @param url file to download
     * @param filename file for storing downloaded content
     */
    Download(QNetworkAccessManager *manager, const QString &url, const QString &filename);

    /**
     * @brief Load an existing download
     * @param manager network access manager
     * @param json serialized JSON data for the download
     */
    Download(QNetworkAccessManager *manager, const QByteArray &json);

    /**
     * @brief Destroy the download
     */
    virtual ~Download();

    /**
     * @brief Retrieve the current progress
     */
    int progress() const;

    /**
     * @brief Retrieve the current state of the download
     */
    State state() const;

    /**
     * @brief Retrieve the URL for the download
     */
    QString url() const;

    /**
     * @brief Retrieve the name of the file
     */
    QString filename() const;

    /**
     * @brief Retrieve the total size of the download
     *
     * This value will be equal to Uninitialized if the probe has not yet been
     * completed and Unknown if no content length was available.
     */
    qint64 size() const;

    /**
     * @brief Retrieve the fragments for the download
     */
    QList<Fragment*> fragments() const;

    /**
     * @brief Retrieve the current error
     *
     * This value will only be set if the current state is Failed.
     */
    QString error() const;

    /**
     * @brief Start the download
     */
    void start();

Q_SIGNALS:

    /**
     * @brief Indicate that the current progress has changed
     */
    void progressChanged();

    /**
     * @brief Indicate that the current state has changed
     */
    void stateChanged();

private Q_SLOTS:

    void onFinished();

    void onError(const QString &message);
    void onAllocationProgress(int value);
    void onAllocationSucceeded();

    void onDataReceived(const QByteArray &data, qint64 offset);

private:

    void init();
    void probe();
    void alloc();
    void download();
    void fail(const QString &message);

    Fragment *newFragment(qint64 start, qint64 end);

    QNetworkAccessManager *mManager;
    QNetworkReply *mReply;

    int mProgress;
    State mState;

    QString mUrl;
    File mFile;
    qint64 mSize;
    QList<Fragment*> mFragments;
    QString mError;
};

#endif // DOWNLOAD_H
