#include "TopicBuilder.h"

TopicBuilder::TopicBuilder(/* args */)
{
}

TopicBuilder::~TopicBuilder()
{
}

String TopicBuilder::Command(const String& id){
    return "iot/devices/" + id + "/command";
}

String TopicBuilder::Status(const String& id){
    return "iot/devices/" + id + "/status";
}

String TopicBuilder::Telemetry(const String& id){
    return "iot/devices/" + id + "/telemetry";
}

String TopicBuilder::Ota(const String& id){
    return "iot/devices/" + id + "/ota";
}