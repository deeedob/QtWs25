#pragma once

#include "event.qpb.h"

#include <QtQmlIntegration/QtQmlIntegration>

#include <QtProtobuf/QProtobufJsonSerializer>
#include <QtProtobuf/QProtobufMessage>
#include <QtProtobuf/QProtobufSerializer>

#include <QtCore/QObject>
#include <QtCore/QString>

#include <cctype>
#include <cstdio>

class Serializer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Type type MEMBER mType NOTIFY typeChanged)

public:
    enum Type { Proto, Json };
    Q_ENUM(Type)

    Q_INVOKABLE QByteArray serialize(const Event &msg)
    {
        return mType == Proto
            ? msg.serialize(&mProtoSerializer)
            : msg.serialize(&mJsonSerializer);
    }

    Q_INVOKABLE QString display(const QByteArray &data)
    {
        QString result;
        for (uchar c : data) {
            result += QChar::isPrint(c)
                ? QChar(c)
                : QString("\\x%1").arg(c, 2, 16, QChar('0')).toUpper();
        }
        return result;
    }

signals:
    void typeChanged();

private:
    Type mType;
    QProtobufSerializer mProtoSerializer;
    QProtobufJsonSerializer mJsonSerializer;
};
