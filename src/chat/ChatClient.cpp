#include "ChatClient.h"
#include <QJsonObject>
#include <QJsonDocument>

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

void ChatClient::sendMessage(const QString &user, const QString &message)
{
    QJsonObject obj;
    obj["type"] = "message";
    obj["user"] = user;
    obj["content"] = message;

    m_socket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

void ChatClient::sendJoin(const QString &user)
{
    QJsonObject obj;
    obj["type"] = "join";
    obj["user"] = user;

    m_socket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

void ChatClient::sendTyping(const QString &user)
{
    QJsonObject obj;
    obj["type"] = "typing";
    obj["user"] = user;
    obj["active"] = !user.isEmpty();

    m_socket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
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