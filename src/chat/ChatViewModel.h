#ifndef CHATVIEWMODEL_H
#define CHATVIEWMODEL_H

#include <QObject>
#include <QStringList>
#include <ChatClient.h>

class ChatViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)

public:
    explicit ChatViewModel(QObject *parent = nullptr);

    QStringList messages() const;

    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void sendMessage(const QString &message);

signals:
    void messagesChanged();

private slots:
    void onMessageReceived(const QString &message);

private:
    ChatClient m_client;
    QStringList m_messages;
};

#endif // CHATVIEWMODEL_H
