#include "ChatViewModel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

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

QString ChatViewModel::username() const
{
    return m_username;
}

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

QString ChatViewModel::typingText() const
{
    if (m_typingUsers.isEmpty())
        return "";

    if (m_typingUsers.size() == 1)
        return m_typingUsers.first() + " está escribiendo...";

    if (m_typingUsers.size() == 2)
        return m_typingUsers[0] + " y " + m_typingUsers[1] + " están escribiendo...";

    return QString::number(m_typingUsers.size()) + " personas están escribiendo...";
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

void ChatViewModel::sendTyping(const QString &user, bool active)
{
    m_client.sendTyping(user, active);
}

void ChatViewModel::onMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (!doc.isObject())
        return;

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();

    if (type == "message") {

        QString user = obj["user"].toString();
        QString content = obj["content"].toString();

        QString formatted = user + ": " + content;

        m_messages.append(formatted);
        emit messagesChanged();

        if (m_typingUsers.contains(user)) {
            m_typingUsers.removeAll(user);
            emit typingTextChanged();
        }
    }

    else if (type == "typing") {
        QString user = obj["user"].toString();
        bool active = obj["active"].toBool();

        if (user.isEmpty() || user == m_username)
            return;

        if (active) {

            if (!m_typingUsers.contains(user)) {
                m_typingUsers.append(user);
                emit typingTextChanged();
            }

        } else {

            if (m_typingUsers.contains(user)) {
                m_typingUsers.removeAll(user);
                emit typingTextChanged();
            }
        }
    }
}