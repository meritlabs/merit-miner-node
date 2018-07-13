/*
 * Copyright (C) 2018 The Merit Foundation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either vedit_refsion 3 of the License, or
 * (at your option) any later vedit_refsion.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give 
 * permission to link the code of portions of this program with the 
 * Botan library under certain conditions as described in each 
 * individual source file, and distribute linked combinations 
 * including the two.
 *
 * You must obey the GNU General Public License in all respects for 
 * all of the code used other than Botan. If you modify file(s) with 
 * this exception, you may extend this exception to your version of the 
 * file(s), but you are not obligated to do so. If you do not wish to do 
 * so, delete this exception statement from your version. If you delete 
 * this exception statement from all source files in the program, then 
 * also delete it here.
 */
#include <node.h>
#include <iostream>
#include <merit/miner.hpp>

merit::Context* context = nullptr;
void set_agent(const v8::FunctionCallbackInfo<v8::Value>& args) {
    assert(context);
    auto isolate = args.GetIsolate();

    if(args.Length() != 2) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "Requests 2 arguments")));
        return;
    }

    if(!args[0]->IsString()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "software must be a string")));
        return;
    }

    if(!args[1]->IsString()) {
        isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "version must be a string")));
        return;
    }
    v8::String::Utf8Value software{args[0]->ToString()};
    v8::String::Utf8Value version{args[1]->ToString()};

    merit::set_agent(context, *software, *version);
}

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

void is_stratum_connected(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);

    auto isolate = args.GetIsolate();

    bool connected = merit::is_stratum_connected(context);
    v8::Local<v8::Boolean> ret = v8::Boolean::New(isolate, connected);
    args.GetReturnValue().Set(ret);
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

void number_of_cores(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();

    auto cores = merit::number_of_cores();
    v8::Local<v8::Number> ret = v8::Number::New(isolate, cores);
    args.GetReturnValue().Set(ret);
}

void stat_to_obj(const merit::MinerStat& s, v8::Local<v8::Object>& obj, v8::Isolate* isolate)
{
    assert(isolate);
    obj->Set(v8::String::NewFromUtf8(isolate, "start"), v8::Number::New(isolate, s.start));

    if(s.seconds > 0) {
        obj->Set(v8::String::NewFromUtf8(isolate, "end"), v8::Number::New(isolate, s.end));
        obj->Set(v8::String::NewFromUtf8(isolate, "seconds"), v8::Number::New(isolate, s.seconds));
        obj->Set(v8::String::NewFromUtf8(isolate, "attempts_per_second"), v8::Number::New(isolate, s.attempts_per_second));
        obj->Set(v8::String::NewFromUtf8(isolate, "cycles_per_second"), v8::Number::New(isolate, s.cycles_per_second));
        obj->Set(v8::String::NewFromUtf8(isolate, "shares_per_second"), v8::Number::New(isolate, s.shares_per_second));
    } 

    obj->Set(v8::String::NewFromUtf8(isolate, "attempts"), v8::Number::New(isolate, s.attempts));
    obj->Set(v8::String::NewFromUtf8(isolate, "cycles"), v8::Number::New(isolate, s.cycles));
    obj->Set(v8::String::NewFromUtf8(isolate, "shares"), v8::Number::New(isolate, s.shares));
}

void miner_stats(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    assert(context);
    auto isolate = args.GetIsolate();

    auto stats = merit::get_miner_stats(context);

    v8::Local<v8::Object> total = v8::Object::New(isolate);
    v8::Local<v8::Object> current = v8::Object::New(isolate);
    v8::Local<v8::Array> history = v8::Array::New(isolate);

    stat_to_obj(stats.total, total, isolate);
    stat_to_obj(stats.current, current, isolate);

    int i = 0;
    for(const auto& s : stats.history) {
        v8::Local<v8::Object> os = v8::Object::New(isolate);
        stat_to_obj(s, os, isolate);
        history->Set(i, os);
        i++;
    }

    v8::Local<v8::Object> ret = v8::Object::New(isolate);
    ret->Set(v8::String::NewFromUtf8(isolate, "total"), total);
    ret->Set(v8::String::NewFromUtf8(isolate, "current"), current);
    ret->Set(v8::String::NewFromUtf8(isolate, "history"), history);
    args.GetReturnValue().Set(ret);
}

void initialize(v8::Handle<v8::Object> exports)
{
    merit::init();
    context = merit::create_context();
    NODE_SET_METHOD(exports, "setAgent", set_agent);
    NODE_SET_METHOD(exports, "connectToStratum", connect_to_stratum);
    NODE_SET_METHOD(exports, "disconnectStratum", disconnect_stratum);
    NODE_SET_METHOD(exports, "isStratumConnected", is_stratum_connected);
    NODE_SET_METHOD(exports, "startMiner", start_miner);
    NODE_SET_METHOD(exports, "stopMiner", stop_miner);
    NODE_SET_METHOD(exports, "isStratumRunning", is_stratum_running);
    NODE_SET_METHOD(exports, "isMinerRunning", is_miner_running);
    NODE_SET_METHOD(exports, "isStratumStopping", is_stratum_stopping);
    NODE_SET_METHOD(exports, "isMinerStopping", is_miner_stopping);
    NODE_SET_METHOD(exports, "numberOfCores", number_of_cores);
    NODE_SET_METHOD(exports, "minerStats", miner_stats);
}

NODE_MODULE(meritminer, initialize);
