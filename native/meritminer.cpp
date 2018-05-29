#include <node.h>
#include <iostream>
#include <merit/miner.hpp>

merit::Context* context = nullptr;

void connect_to_stratum(const v8::FunctionCallbackInfo<v8::Value>& args) {
    assert(context);
    auto isolate = args.GetIsolate();

    if(args.Length() != 2) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "Requests 2 arguments")));
        return;
    }

    if(!args[0]->IsString()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "stratum url must be a string")));
        return;
    }

    if(!args[1]->IsString()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "address must be a string")));
        return;
    }

    v8::String::Utf8Value stratum_url{args[0]->ToString()};
    v8::String::Utf8Value address{args[1]->ToString()};

    if(!merit::connect_stratum(context, *stratum_url, *address, "foobar")) {
        isolate->ThrowException(v8::Exception::Error(
                    v8::String::NewFromUtf8(isolate, "Error connecting to the stratum pool")));
        return;
    }
    merit::run_stratum(context);
}

void disconnect_stratum(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    merit::disconnect_stratum(context);
    merit::stop_stratum(context);

    auto isolate = args.GetIsolate();
    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "stopped stratum"));
}

void start_miner(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);
    auto isolate = args.GetIsolate();

    if(args.Length() != 2) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "Requests 2 arguments")));
        return;
    }
    if(!args[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "workers argument must be a number")));
        return;
    }
    if(!args[1]->IsNumber()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "threads argument must be a number")));
        return;
    }

    int workers = args[0]->NumberValue();
    int worker_threads = args[1]->NumberValue();

    merit::run_miner(context, workers, worker_threads);

    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "started miner"));
}

void stop_miner(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);
    merit::stop_miner(context);
}

void is_stratum_running(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);

    auto isolate = args.GetIsolate();

    bool running = merit::is_stratum_running(context);
    v8::Local<v8::Boolean> ret = v8::Boolean::New(isolate, running);
    args.GetReturnValue().Set(ret);
}

void is_miner_running(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);

    auto isolate = args.GetIsolate();

    bool running = merit::is_miner_running(context);
    v8::Local<v8::Boolean> ret = v8::Boolean::New(isolate, running);
    args.GetReturnValue().Set(ret);
}

void is_stratum_stopping(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);

    auto isolate = args.GetIsolate();

    bool stopping = merit::is_stratum_stopping(context);
    v8::Local<v8::Boolean> ret = v8::Boolean::New(isolate, stopping);
    args.GetReturnValue().Set(ret);
}

void is_miner_stopping(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);

    auto isolate = args.GetIsolate();

    bool stopping = merit::is_miner_stopping(context);
    v8::Local<v8::Boolean> ret = v8::Boolean::New(isolate, stopping);
    args.GetReturnValue().Set(ret);
}

void initialize(v8::Handle<v8::Object> exports)
{
    context = merit::create_context();
    NODE_SET_METHOD(exports, "connectToStratum", connect_to_stratum);
    NODE_SET_METHOD(exports, "disconnectStratum", disconnect_stratum);
    NODE_SET_METHOD(exports, "startMiner", start_miner);
    NODE_SET_METHOD(exports, "stopMiner", stop_miner);
    NODE_SET_METHOD(exports, "isStratumRunning", is_stratum_running);
    NODE_SET_METHOD(exports, "isMinerRunning", is_miner_running);
    NODE_SET_METHOD(exports, "isStratumStopping", is_stratum_stopping);
    NODE_SET_METHOD(exports, "isMinerStopping", is_miner_stopping);
}

NODE_MODULE(meritminer, initialize);
