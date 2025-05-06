#include "event.qpb.h"

#include <QtProtobuf/QProtobufSerializer>
#include <QtProtobuf/QProtobufJsonSerializer>

#include <iostream>

using namespace Qt::Literals::StringLiterals;

void printSerialized(QAnyStringView qtdata)
{
    auto data = qtdata.toString().toStdString();
    for (char c : data)
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << c;
        else
            std::printf("\\x%02x", c);
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    Event e1;
    e1.setType(Event::Type::USER);
    e1.setName("User.json");

    Event e2;
    e2.setType(Event::Type::SYSTEM);
    e2.setName("Sys.proto");

    QProtobufSerializer protoSer;
    QProtobufJsonSerializer jsonSer;
    printSerialized("JSON: "
        + e1.serialize(&jsonSer));
    printSerialized("PROTO: "
        + e2.serialize(&protoSer));
}
