#include "ChatClient.h"
#include <QJsonObject.h>
#include <QJsonDocument.h>

ChatClient::ChatClient(QObject *parent)
    : QObject(parent)
{
    connect(&m_socket, &QWebSocket::connected, this, &ChatClient::onConnected);
    connect(&m_socket, &QWebSocket::textMessageReceived, this, &ChatClient::onTextMessageReceived);
    connect(&m_socket, &QWebSocket::disconnected, this, &ChatClient::onDisconnected);
}

void ChatClient::connectToServer(const QUrl &url)
{
    m_socket.open(url);
}

void ChatClient::sendMessage(const QString &message)
{
    QJsonObject obj;
    obj["user"] = "Rober";
    obj["content"] = message;
    obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(obj);
    m_socket.sendTextMessage(doc.toJson(QJsonDocument::Compact));
}

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