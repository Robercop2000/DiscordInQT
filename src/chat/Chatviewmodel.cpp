#include "ChatViewModel.h"
#include <QJsonDocument>
#include <QJsonObject>

ChatViewModel::ChatViewModel(QObject *parent)
    : QObject(parent)
{
    connect(&m_client, &ChatClient::messageReceived,
            this, &ChatViewModel::onMessageReceived);

    connect(&m_client, &ChatClient::connected, [this]() {
        m_connected = true;
        emit isConnectedChanged();
        m_client.sendJoin(m_username);
    });

    connect(&m_client, &ChatClient::disconnected, [this]() {
        m_connected = false;
        emit isConnectedChanged();
    });
}

QString ChatViewModel::username() const { return m_username; }

void ChatViewModel::setUsername(const QString &name)
{
    if (m_username == name)
        return;

    m_username = name;
    emit usernameChanged();
}

QStringList ChatViewModel::messages() const
{
    return m_messages;
}

bool ChatViewModel::isConnected() const
{
    return m_connected;
}

QString ChatViewModel::typingUser() const
{
    return m_typingUser;
}

void ChatViewModel::connectToServer()
{
    m_client.connectToServer(QUrl("ws://localhost:3000"));
}

void ChatViewModel::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    m_client.sendMessage(m_username, message);
}

void ChatViewModel::onMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "message") {
        QString formatted = obj["user"].toString() + ": " + obj["content"].toString();
        m_messages.append(formatted);
        emit messagesChanged();
    }

    if (type == "typing") {
        QString user = obj["user"].toString();
        bool active = obj["active"].toBool();

        if (user != m_username) {
            if (active)
                m_typingUser = user;
            else
                m_typingUser.clear();

            emit typingUserChanged();
        }
    }
}

void ChatViewModel::sendTyping(const QString &user)
{
    m_client.sendTyping(user);
}