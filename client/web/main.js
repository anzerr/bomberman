var WebSocketServer = require('ws').Server;
var app = require('express')();
var http = require('http').Server(app);

var docker = require('./server/docker.js');

docker.build(function() {
    var map = new (require('./server/map.js'))();

    app.get('/', function(req, res){
        res.sendFile(__dirname + '/public/index.html');
    });

    app.post('/game', function(req, res){

    });

    var fs = require('fs');
    var WebSocketServer = require('ws').Server;

    var wss = new WebSocketServer({port: 8080, host: '0.0.0.0'});
    wss.on('connection', function(ws) {
        if (!map.add(ws)) {
            ws.close();
        }
    });

    http.listen(3000, function(){
        console.log('listening on *:3000');
    });
});