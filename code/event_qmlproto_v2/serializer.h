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
    Q_PROPERTY(Event event MEMBER mEvent NOTIFY eventChanged)
    Q_PROPERTY(QByteArray data READ data NOTIFY dataChanged)

public:
    enum Type { Proto, Json }; Q_ENUM(Type)
    Serializer(QObject *parent = nullptr)
        : QObject(parent)
    {
        connect(this, &Serializer::typeChanged, this, &Serializer::serialize);
        connect(this, &Serializer::eventChanged, this, &Serializer::serialize);
    }

    void serialize()
    {
        mData = mType == Proto
            ? mEvent.serialize(&mProtoSerializer)
            : mEvent.serialize(&mJsonSerializer);
        emit dataChanged();
    }

    QByteArray data() const { return mData; }

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
    void eventChanged();
    void dataChanged();

private:
    Type mType;
    Event mEvent;
    QByteArray mData;
    QProtobufSerializer mProtoSerializer;
    QProtobufJsonSerializer mJsonSerializer;
};
