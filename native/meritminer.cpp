#include <node.h>
#include <iostream>
#include <merit/miner.hpp>


void StartMiner(const v8::FunctionCallbackInfo<v8::Value>& args) {
    std::cerr << "Doing Stuff!" << std::endl;
    merit::test();
    auto isolate = args.GetIsolate();
    args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "Starting Miner"));
}


void Initialize(v8::Handle<v8::Object> exports) {
    NODE_SET_METHOD(exports, "startMiner", StartMiner);
}



NODE_MODULE(meritminer, Initialize);
