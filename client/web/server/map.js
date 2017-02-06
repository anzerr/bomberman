
var game = require('./game.js');

var obj = function(config) {
	this._config = config;
	this._user = {};
	this._client = {};
	this._handle = new game(this);
	for (var i = 0; i < 4; i++) {
		this._client[i] = this.createClient(i);
	}
};
obj.prototype = {
	id: function() {
		return (this._config.id);
	},
	slot: function() {
		var c = 0;
		for (var x in this._user) {
			if (this._user[x]) {
				c += 1;
			}
		}
		return (c);
	},
	createClient: function(key) {
		var self = this, s = require('net').Socket();
		s.connect(this._config.port, (process.platform == 'win32') ? '192.168.99.100' : '127.0.0.1');

		s.on('data', function(d) {
			self._handle.action(key, d.toString());
		});

		s.on('connect', function() {
			console.log(key, 'is connected');
		});

		s.on('close', function() {
			console.log(key, 'is disconnected');
			self._client[key] = null;
			var free = 0;
			for (var i in self._client) {
				if (!self._client[i]) {
					free += 1;
				}
			}
			if (free == 4 && self._config.hook) {
				self._config.hook();
			}
		});

		s.on('error', function(e) {
			console.log('error on', key, e);
		});
		return (s);
	},
	add: function(socket) {
		for (var i = 0; i < 4; i++) {
			if (!this._user[i]) {
				var self = this;
				(function(key) {
					self._user[key] = socket;
					socket.on('message', function(data, flags) {
						self._handle.message(key, data);
					});
					socket.on('close', function() {
						self._user[key] = null;
					});
				})(i);
				return (1);
			}
		}
		return (0);
	}
};

module.exports = obj;