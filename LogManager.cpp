/*
 * MIT License
 *
 * Copyright (c) 2019 Christopher Joseph Dean Schaefer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "LogManager.h"

static char SeverityText[6][20] =
{
        "[TRACE] ",
        "[DEBUG] ",
        "[INFO] ",
        "[WARNING] ",
        "[ERROR] ",
        "[FATAL] "
};

LogManager* LogManager::mInstance;

LogManager::LogManager(const std::string& filename, SeverityLevel severityLevel)
        : mFileStream(filename),
          mSeverityLevel(severityLevel)
{
}

LogManager::~LogManager()
{
}

void LogManager::Create(const std::string& filename, SeverityLevel severityLevel)
{
    LogManager::mInstance = new LogManager(filename, severityLevel);
}

void LogManager::Destroy()
{
    delete LogManager::mInstance;
}

LockedStream Log(SeverityLevel severityLevel)
{
    if (severityLevel >= LogManager::mInstance->mSeverityLevel)
    {
        return LockedStream(LogManager::mInstance->mFileStream, LogManager::mInstance->mMutex);
    }
    else
    {
        return LockedStream(LogManager::mInstance->mNullStream, LogManager::mInstance->mMutex);
    }
};