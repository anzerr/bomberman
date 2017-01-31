var connect = require('connect');
var serveStatic = require('serve-static');
connect().use(serveStatic(__dirname)).listen(1337);

var WebSocketServer = require('ws').Server;
var wss = new WebSocketServer({ port: 8080 });

wss.on('connection', function connection(ws) {
    ws.on('message', function incoming(message) {
        console.log('received: %s', message);
    });

    ws.send('something');
});

/*var a = function () {
    var s = require('net').Socket();

    s.connect(1337, '127.0.0.1');

    s.write('cat\r\n', function(e, r) {
        console.log('send msg', e, r);
    });

    s.on('data', function(d) {
        console.log('--', d.toString());
    });

    s.on('connect', function() {
        console.log('connected');
    });

    s.on('close', function() {
        console.log('closed');
        setTimeout(a, 5000);
    });

    s.on('error', function(e) {
        console.log('e', e);
    });
};
a();*/