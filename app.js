var fs = require('fs');
var http = require('http');
const WebSocket = require('ws');

function requestHandler(request, response) {
    fs.readFile('./index.html', function(error, content) {
        response.writeHead(200, {
            'Content-Type': 'text/html'
        });
        response.end(content);
    });
}

// create http server
var server = http.createServer(requestHandler)
var ws = new WebSocket.Server({
    server
});

let sockets = [];


function broadcast(socket, data) {
    for (var i = 0; i < sockets.length; i++) {
        if (sockets[i] != socket) {
            sockets[i].send(data);
        }
    }
}



ws.on('connection', function(socket, req) {
    sockets.push(socket);
    socket.on('message', function(message) {
        console.log('received: %s', message);

        //  to esp
        if (message == 'DEVICE1_ON') {
            data='LED_ON';
            broadcast(socket,data); 
        }

        if (message == 'DEVICE1_OFF') {
            data='LED_OFF';
            broadcast(socket,data); 
        }

            //SENSER
        if (message == 'SENSER_DEVICE1_DISABLE') {
            data='SENSER_DEVICE1_DISABLE';
            broadcast(socket,data); 
        }

        
        if (message == 'SENSER_DEVICE1_ACTIVE') {
            data='SENSER_DEVICE1_ACTIVE';
            broadcast(socket,data); 
        }




        //ESP to web control
         if (message == 'DEVICE1_ON') {
            data=JSON.stringify({ status: "success", content: "LED 1 BẬT", data:message+"" })
            broadcast(socket,data); 
        }

        if (message == 'DEVICE1_OFF') {
            data=JSON.stringify({ status: "success", content: "LED 1 TẮT", data:message+"" })
            broadcast(socket,data); 
        }

             // SENSER
        if (message == 'SENSER_DEVICE1_DISABLE') {
            data=JSON.stringify({ status: "success", content: "DISABLE SENSER ", data:message+"" })
            broadcast(socket,data); 
        }

        if (message == 'SENSER_DEVICE1_ACTIVE') {
            data=JSON.stringify({ status: "success", content: "ACTIVE SENSER", data:message+"" })
            broadcast(socket,data); 
        }

    });
    
    socket.on('close', function() {
        console.log('disconnected');
    });

    setInterval(()=>{
        // get thoi gian hen gio o db 
       const time =new Date('Sat Sep 25 2021 16:56:20 GMT+0700').getTime()
        console.log(time);
        if(time < new Date().getTime() ){
            data='LED_OFF';
            broadcast(socket,data); 
        }
    }
    , 5000)
    
});

server.listen(3000, () => console.log('http://localhost:3000'))