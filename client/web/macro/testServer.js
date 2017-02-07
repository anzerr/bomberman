var client = function() {
    this._map = [];
    this._player = {

    }
};
client.prototype = {
    _updatePlayer: function(data) {
        data = data.split(',');
        if (data[0] == 'p') {
            this._player[data[1]] = {
                name: data[2],
                dead: data[3],
                x: data[4],
                y: data[5]
            };
        }
    },
    drawMap: function() {
        console.log('------------');
        for (var x = 0; x < 10; x++) {
            var str = '|';
            for (var y = 0; y < 10; y++) {
                var found = false;
                for (var i in this._player) {
                    if (this._player[i].x == x && this._player[i].y == y) {
                        found = true;
                        str += '0';
                        break;
                    }
                }
                if (!found) {
                    str += ' ';
                }
            }
            console.log(str + '|');
        }
        console.log('------------');
    },
    action: function(data) {
        data =data.split(';');
        for (var i in data) {
            if (data[i][0] == 'p') {
                this._updatePlayer(data[i]);
            }
        }
    }
};


var a = function(id) {
    var s = require('net').Socket();
    s.connect(980, '127.0.0.1');
    var handle = new client();
    /*if (id == 0) {
        setTimeout(function() {
            s.end();
        }, 5000);
    }*/

    var action = [
        'u',
        'd',
        'l',
        'r'
    ];
    var run = function() {
        s.write(action[Math.floor(Math.random() * action.length)], function(e, r) {
            setTimeout(function() {
                run();
            }, 100);
        });
    };
    run();

    s.on('data', function(d) {
        handle.action(d.toString());
        if (id == 0) {
            handle.drawMap();
        }
	    //console.log('--', d.toString());
    });

    s.on('connect', function() {
	    /*console.log('connected');
        s.write(id + '_is_id\n', function(e, r) {
            console.log('send msg', e, r);
        });*/
    });

    s.on('close', function() {
	    //console.log('closed');
	    //setTimeout(a, 5000);
    });

    s.on('error', function(e) {
	    //console.log('e', e);
    });
};
for (var i = 0; i < 4; i++) {
    a(i);
}
