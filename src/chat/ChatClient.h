#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QWebSocket>

class ChatClient : public QObject
{
    Q_OBJECT

public:
    explicit ChatClient(QObject *parent = nullptr);

    Q_INVOKABLE void connectToServer(const QUrl &url);
    Q_INVOKABLE void sendMessage(const QString &message);

signals:
    void connected();
    void messageReceived(const QString &message);
    void disconnected();

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);
    void onDisconnected();

private:
    QWebSocket m_socket;
};

#endif // CHATCLIENT_H
