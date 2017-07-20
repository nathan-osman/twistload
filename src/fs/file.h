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

#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QObject>
#include <QThread>

class AllocationTask;

/**
 * @brief File supporting pre-allocation and random writes
 *
 * When downloading multiple parts of a file at the same time, a file object
 * capable of pre-allocating the required size and writing to random locations
 * within the file is required.
 */
class File : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create a new file
     *
     * The filename must be set with setFilename().
     */
    File();

    /**
     * @brief Create a new file
     */
    explicit File(const QString &filename);

    /**
     * @brief Destroy the file object
     *
     * If allocation is in progress, this will block until the allocation
     * is successfully interrupted.
     */
    virtual ~File();

    /**
     * @brief Retrieve the filename
     */
    QString filename() const;

    /**
     * @brief Set the filename
     */
    void setFilename(const QString &filename);

    /**
     * @brief Open the file for writing
     *
     * This method opens the file for writing and ensures that if size is
     * non-zero, empty data is written to the file to make it the requested
     * size. The finished() signal is emitted when this completes.
     */
    void open(qint64 size);

    /**
     * @brief Write data to the file at the specified location
     */
    bool write(const QByteArray &data, qint64 offset);

    /**
     * @brief Close the file
     */
    void close();

Q_SIGNALS:

    /**
     * @brief Indicate an error occurred during allocation or writing
     */
    void error(const QString &message);

    /**
     * @brief Indicate allocation progress
     * @param value integer between 0 and 100 inclusive
     */
    void allocationProgress(int value);

    /**
     * @brief Indicate that the file has successfully been allocated
     *
     * The file will be open for writing.
     */
    void allocationSucceeded();

private Q_SLOTS:

    void onSucceeded();

private:

    QThread mThread;
    AllocationTask *mTask;

    QFile mFile;
};

#endif // FILE_H
