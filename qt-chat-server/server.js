const WebSocket = require('ws');

const PORT = 3000;
const wss = new WebSocket.Server({ port: PORT });

const clients = new Set();

wss.on('connection', (ws) => {
    console.log("Cliente conectado");

    clients.add(ws);

    ws.on('message', (data) => {
        console.log("Mensaje:", data.toString());

        // Broadcast
        clients.forEach(client => {
            if (client.readyState === WebSocket.OPEN) {
                client.send(data.toString());
            }
        });
    });

    ws.on('close', () => {
        console.log("Cliente desconectado");
        clients.delete(ws);
    });
});

console.log(`Servidor corriendo en ws://localhost:${PORT}`);