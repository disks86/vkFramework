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
#ifndef VKFRAMEWORK_LOGMANAGER_H
#define VKFRAMEWORK_LOGMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

enum SeverityLevel
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

class NullBuffer
        : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};

class NullStream
        : public std::ostream
{
private:
    NullBuffer obj;
public:
    NullStream()
            : std::ostream(&obj)
    {
    }
};

class LockedStream
{
    std::unique_lock<std::mutex> mLock;
    std::ostream* mStream;

public:
    LockedStream(std::ostream& stream, std::mutex& mutant)
            : mStream(&stream),
              mLock(mutant)
    {
    }

    LockedStream(LockedStream&& obj) noexcept
            : mLock(std::move(obj.mLock))
            , mStream(obj.mStream)
    {
        obj.mStream = nullptr;
    }

    friend LockedStream&& operator << (LockedStream&& ls, std::ostream& (*argument)(std::ostream&))
    {
        (*ls.mStream) << argument;
        return std::move(ls);
    }

    friend LockedStream&& operator << (LockedStream&& ls, uint32_t&& argument)
    {
        (*ls.mStream) << argument;
        return std::move(ls);
    }

    template <typename ArgumentType>
    friend LockedStream&& operator << (LockedStream&& ls, ArgumentType&& argument)
    {
        (*ls.mStream) << std::forward<ArgumentType>(argument);
        return std::move(ls);
    }
};

class LogManager
{
private:
    static LogManager* mInstance;

    std::mutex mMutex;
    std::ofstream mFileStream;
    NullStream mNullStream;
    SeverityLevel mSeverityLevel;

public:
    LogManager(const std::string& filename, SeverityLevel severityLevel);
    ~LogManager();
    static void Create(const std::string& filename, SeverityLevel severityLevel);
    static void Destroy();

    friend LockedStream Log(SeverityLevel severityLevel);
};

LockedStream Log(SeverityLevel severityLevel);


#endif //VKFRAMEWORK_LOGMANAGER_H
