/*
 * Copyright (C) 2023 Xiaomi Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TestService"

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>

#include "BnTestStuff.h"

#include <utils/Log.h>
#include <utils/String8.h>

using namespace android;
using android::binder::Status;

namespace android {
class ITestServer : public BnTestStuff {
public:
    // ITestServer::read()
    Status read(int32_t sample)
    {
        ALOGI("ITestServer::read() called %" PRIi32 ", start do hard work", sample);
        return Status::ok();
    }

    // ITestServer::write()
    Status write(int32_t index)
    {
        ALOGI("ITestServer::write() called %" PRIi32 ", start do hard work", index);
        return Status::ok();
    }
};
} // namespace android

extern "C" int main(int argc, char** argv)
{
    ALOGI("sample service start count: %d, argv[0]: %s", argc, argv[0]);

    // obtain service manager
    sp<IServiceManager> sm(defaultServiceManager());
    ALOGI("defaultServiceManager(): %p", sm.get());
    sp<ITestServer> testServer = new ITestServer;

    // add service
    sm->addService(String16("aidldemo.service"), testServer);
    ALOGI("add aidldemo.service to service manager");

    // start worker thread
    ProcessState::self()->startThreadPool();

    // join the main thread
    IPCThreadState::self()->joinThreadPool();
    return 0;
}