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

#include <QMetaObject>

#include "allocationtask.h"
#include "file.h"

File::File(const QString &filename)
    : mTask(nullptr),
      mFile(filename)
{
}

File::~File()
{
    if (mTask) {
        mTask->abort();
        mThread.wait();
    }
}

void File::open(qint64 size)
{
    if (size) {

        // Create a new thread and task and move the task to the thread
        mTask = new AllocationTask(mFile.fileName(), size);
        mTask->moveToThread(&mThread);

        // Ensure the task and thread are destroyed when complete
        connect(mTask, &AllocationTask::progress, this, &File::allocationProgress);
        connect(mTask, &AllocationTask::error, this, &File::allocationError);
        connect(mTask, &AllocationTask::succeeded, this, &File::onSucceeded);
        connect(mTask, &AllocationTask::finished, this, [=]() {
            mTask->deleteLater();
            mTask = nullptr;
            mThread.quit();
        });

        // Start the thread and invoke the slot
        mThread.start();
        QMetaObject::invokeMethod(mTask, "run", Qt::QueuedConnection);
    }
}

bool File::write(const QByteArray &data, qint64 offset)
{
    if (!mFile.seek(offset) || mFile.write(data) == -1) {
        emit error(mFile.errorString());
        return false;
    }
    return true;
}

void File::close()
{
    mFile.close();
}

void File::onSucceeded()
{
    // Attempt to open the file for writing
    if (!mFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        emit error(mFile.errorString());
        return;
    }

    emit allocationSucceeded();
}
