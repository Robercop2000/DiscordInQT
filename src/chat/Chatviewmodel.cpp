#include "Chatviewmodel.h"
#include "Chatclient.h"

ChatViewModel::ChatViewModel(QObject *parent)
    : QObject(parent)
{
    connect(&m_client, &ChatClient::messageReceived,
            this, &ChatViewModel::onMessageReceived);
}

QStringList ChatViewModel::messages() const
{
    return m_messages;
}

void ChatViewModel::connectToServer()
{
    m_client.connectToServer(QUrl("ws://localhost:3000"));
}

void ChatViewModel::sendMessage(const QString &message)
{
    m_client.sendMessage(message);
}

void ChatViewModel::onMessageReceived(const QString &message)
{
    m_messages.append(message);
    emit messagesChanged();
}