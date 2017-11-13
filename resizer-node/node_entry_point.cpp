#include <nan.h>

using namespace v8;
using namespace Nan;

void resize(const Nan::FunctionCallbackInfo<v8::Value>& info);

NAN_MODULE_INIT(initModule)
{
    target->Set(New("resize").ToLocalChecked(),
        New<FunctionTemplate>(resize)->GetFunction());
}

NODE_MODULE(resizer, initModule)

void resize(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    info.GetReturnValue().Set(New("world").ToLocalChecked());
}
