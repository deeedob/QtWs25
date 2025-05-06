#include "event.pb.h"

#include <google/protobuf/util/json_util.h>

#include <iostream>
#include <string>

void printSerialized(std::string_view data)
{
    for (char c : data)
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << c;
        else
            std::printf("\\x%02x", c);
    std::cout << std::endl;
}

std::string messageToJsonString(const google::protobuf::Message& message)
{
    std::string out;
    assert(google::protobuf::util::MessageToJsonString(message, &out).ok());
    return out;
}

int main(int argc, char *argv[])
{
    Event e1;
    e1.set_type(Event::USER);
    e1.set_name("User.json");

    Event e2;
    e2.set_type(Event::SYSTEM);
    e2.set_name("Sys.proto");

    printSerialized("JSON : "
        + messageToJsonString(e1));
    printSerialized("PROTO: "
        + e2.SerializeAsString());
}
