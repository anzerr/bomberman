var WebSocketServer = require('ws').Server;
var app = require('express')();
var http = require('http').Server(app);

var map = require('./server/map.js');
var docker = require('./server/docker.js');
var config = {
    web: 3000,
    socket: 8080,
    range: [980, 2999],
    build: true
};

function randId() {
    return Math.random().toString(36).substr(2, 10);
}

var _givePort = {};
var getPort = (function() {
    return function() {
        var range = config.range[1]  - config.range[0], i = Math.floor(Math.random() * range);
        while (_givePort[i + config.range[0]]) {
            i = Math.floor(Math.random() * range);
        }
        _givePort[i + config.range[0]] = true;
        return (i + config.range[0]);
    }
})();

docker.build(config.build, function() {
    var room = [];

    app.get('/', function(req, res) {
        res.sendFile(__dirname + '/public/index.html');
    });

    app.get('/game', function(req, res) {
        var obj = {};
        for (var i in room) {
            obj[room[i].id()] = room[i].slot();
        }
        res.json(obj);
    });

    app.post('/game', function(req, res) {
        var id = randId(), data = {id: id, port: getPort(), hook: function() {
            _givePort[data.port] = false;
            for (var i in room) {
                if (room[i].id() == id) {
                    room.splice(i, 1);
                    break;
                }
            }
        }};
        docker.create(data, function() {
            room.push(new map(data));
            res.json({game: id});
        });
    });

    var fs = require('fs');
    var WebSocketServer = require('ws').Server;

    var wss = new WebSocketServer({port: config.socket, host: '0.0.0.0'});
    wss.on('connection', function(ws) {
        var join = false;
        ws.on('message', function(data, flags) {
            if (join) {
                return
            }
            for (var i in room) {
                if (room[i].id() == data) {
                    if (room[i].add(ws)) {
                        join = true;
                    } else {
                        console.log('failed to join');
                    }
                    break;
                }
            }
        });

        /*if (!map.add(ws)) {
            ws.close();
        }*/
    });

    http.listen(config.web, function(){
        console.log('listening on *:3000');
    });
});