const WebSocket = require('ws');

const PORT = 3000;

// Crear servidor
const wss = new WebSocket.Server({ port: PORT });

// Lista de clientes
const clients = new Set();

wss.on('connection', (ws) => {
    console.log("Cliente conectado");

    clients.add(ws);

    ws.on('message', (data) => {
        try {
            const message = JSON.parse(data);

            console.log("Mensaje recibido:", message);

            // Broadcast a todos
            clients.forEach(client => {
                if (client.readyState === WebSocket.OPEN) {
                    client.send(JSON.stringify(message));
                }
            });

        } catch (err) {
            console.error("Error parsing JSON:", err);
        }
    });

    ws.on('close', () => {
        console.log("Cliente desconectado");
        clients.delete(ws);
    });
});

console.log(`Servidor corriendo en ws://localhost:${PORT}`);