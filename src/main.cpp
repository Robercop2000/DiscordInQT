#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chat/ChatViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ChatViewModel chatViewModel;
    engine.rootContext()->setContextProperty("chatViewModel", &chatViewModel);

    engine.loadFromModule("DiscordInQT", "Main");

    return app.exec();
}
