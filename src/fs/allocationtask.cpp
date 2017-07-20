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

#include <QFile>
#include <QMutexLocker>

#include "allocationtask.h"

const qint64 BlockSize = 65536;

AllocationTask::AllocationTask(const QString &filename, qint64 size)
    : mFilename(filename),
      mSize(size),
      mAbort(false)
{
}

void AllocationTask::abort()
{
    QMutexLocker locker(&mMutex);
    Q_UNUSED(locker)

    mAbort = true;
}

void AllocationTask::run()
{
    // Open the file for writing (without truncating it)
    QFile file(mFilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit error(file.errorString());
        emit finished();
        return;
    }

    // Determine how much data remains to be written and create a block of
    // zero-initialized memory to write to the file
    qint64 remaining = mSize - file.size();
    const char block[BlockSize] = {};

    // Write blocks to the file until it reaches the desired size
    while (remaining > 0) {

        // Lock the mutex and check if the operation should be aborted
        {
            QMutexLocker locker(&mMutex);
            Q_UNUSED(locker)

            if (mAbort) {
                break;
            }
        }

        // Write another block to the file
        qint64 bytesWritten = file.write(block, qMin(BlockSize, remaining));
        if (bytesWritten == -1) {
            emit error(file.errorString());
            emit finished();
            break;
        }
        remaining -= bytesWritten;

        // Emit the progress signal
        double p = 1.0 - static_cast<double>(remaining) / static_cast<double>(mSize);
        emit progress(static_cast<int>(p * 100));
    }

    emit succeeded();
    emit finished();
}
