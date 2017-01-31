
var obj = function(game) {
	this.game = game;
};
obj.prototype = {
	_type: {
		p: function(self, key, data) {
			self.game._player[data[1]] = {
				name: data[2],
				dead: Number(data[3]),
				x: Number(data[4]),
				y: Number(data[5])
			};
			self.game.sendAll(JSON.stringify({
				action: 'player',
				data: self.game._player
			}));
		},
		m: function(self, key, data) {
			var size = data[1], mat = [];
			for (var x = 0; x < size; x++) {
				mat[x] = [];
				for (var y = 0; y < size; y++) {
					mat[x][y] = data[2 + (x * 10) + y];
				}
			}
			self.game._map = {
				size: data[1],
				matrix: mat
			};

			self.game.sendAll(JSON.stringify({
				action: 'map',
				data: self.game._map
			}));
		}
	},

	run: function(key, type, data) {
		if (this._type[type]) {
			this._type[type](this, key, data);
		}
	}
};

module.exports = obj;