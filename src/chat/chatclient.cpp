#include "chatclient.h"

void ChatClient::onConnected()
{
    emit connected();
}

void ChatClient::onTextMessageReceived(const QString &message)
{
    emit messageReceived(message);
}

void ChatClient::onDisconnected()
{
    emit disconnected();
}