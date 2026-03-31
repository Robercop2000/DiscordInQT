const WebSocket = require('ws');

const PORT = 3000;
const wss = new WebSocket.Server({ port: PORT });

const clients = new Set();

wss.on('connection', (ws) => {
    console.log("Cliente conectado");

    clients.add(ws);

    ws.on('message', (data) => {
        let msg;

        try {
            msg = JSON.parse(data);
        } catch {
            return;
        }

        // Guardar usuario
        if (msg.type === "join") {
            ws.user = msg.user;
        }

        // Broadcast a todos
        clients.forEach(client => {
            if (client.readyState === WebSocket.OPEN) {
                client.send(JSON.stringify(msg));
            }
        });
    });

    ws.on('close', () => {
        clients.delete(ws);
        console.log("Cliente desconectado");
    });
});

console.log(`Servidor en ws://localhost:${PORT}`);