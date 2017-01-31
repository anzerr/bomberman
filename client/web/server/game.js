
var action = require('./action.js');

var obj = function(core) {
	this.core = core;
	this._interface = new action(this);
	this._player = {};
	this._map = {};
	this.ping();
};
obj.prototype = {
	ping: function() {
		if (this.core._client[0]) {
			this.core._client[0].write('0', function(e, r) {
				//console.log('wat', e, r);
			});
		}
		var self = this;
		setTimeout(function() {
			self.ping();
		}, 1000 / 16);
	},
	action: function(key, data) {
		data = data.split(';');
		for (var i in data) {
			this._interface.run(key, data[i][0], data[i].split(','));
		}
	},
	message: function(key, data) {
		var action = {
			up: 'u',
			down: 'd',
			left: 'l',
			right: 'r',
			bomb: 'b',
			ping: '0'
		};
		//console.log(key, data);
		if (this.core._client[key] && action[data]) {
			this.core._client[key].write(action[data], function(e, r) {
				//console.log('wat', e, r);
			});
		}
		if (data == 'map') {
			this.send(JSON.stringify({
				action: 'map',
				data: this._map
			}), key);
		}
		if (data == 'player') {
			this.send(JSON.stringify({
				action: 'player',
				data: this._player
			}), key);
		}
	},

	sendAll: function(data, key) {
		for (var i in this.core._user) {
			if (key != i || key == undefined) {
				this.send(data, i);
			}
		}
	},
	sendOther: function(data, key) {
		this.sendAll(data, key)
	},
	send: function(data, key) {
		if (this.core._user[key]) {
			//console.log('send socket c', key, data);
			this.core._user[key].send(data);
		}
	}
};

module.exports = obj;