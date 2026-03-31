#ifndef CHATVIEWMODEL_H
#define CHATVIEWMODEL_H

#include <QObject>
#include <QStringList>
#include "ChatClient.h"

class ChatViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString typingUser READ typingUser NOTIFY typingUserChanged)

public:
    explicit ChatViewModel(QObject *parent = nullptr);

    QStringList messages() const;
    bool isConnected() const;

    QString username() const;
    void setUsername(const QString &name);

    QString typingUser() const;

    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE void sendTyping(const QString &user);

signals:
    void messagesChanged();
    void isConnectedChanged();
    void usernameChanged();
    void typingUserChanged();

private slots:
    void onMessageReceived(const QString &message);

private:
    ChatClient m_client;
    QStringList m_messages;
    bool m_connected = false;
    QString m_username = "User";
    QString m_typingUser;
};

#endif // CHATVIEWMODEL_H
