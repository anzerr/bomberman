
var spawn = require('child_process').spawn;

var obj = function() {
	this._env = {
		"DOCKER_TLS_VERIFY": "1",
		"DOCKER_HOST": "tcp://192.168.99.100:2376",
		"DOCKER_CERT_PATH": this.getUserHome() + '\\.docker\\machine\\machines\\default', //"C:\\Users\\Paris\\.docker\\machine\\machines\\default",
		"DOCKER_MACHINE_NAME": "default"
	};
};
obj.prototype = {
	getUserHome: function() {
		return process.env[(process.platform == 'win32') ? 'USERPROFILE' : 'HOME'];
	},
	bash: function(cmd, env, cd, verbose) {
		var b;
		if (env) {
			b = spawn('sh', ['-c', cmd], {env: env});
		} else {
			b = spawn('sh', ['-c', cmd]);
		}


		b.stdout.on('data', function(data) {
			if (verbose) {
				console.log(data.toString());
			}
		});

		b.stderr.on('data', function(data) {
			if (verbose) {
				console.log(data.toString());
			}
		});

		b.on('close', function() {
			cd();
		});
	},

	create: function(data, cd) {
		var e = (process.platform == 'win32') ? this._env : null;
		return (this.bash('docker run -d --name ' + data.id + 'bomb -p ' + data.port + ':980 server/bomberman:1.0.0', e, function() {
			cd();
		}, true));
	},

	build: function(build, cb) {
		if (!build) {
			return (cb());
		}

		var self = this, run = function() {
			console.log(self._env);
			return (self.bash('docker build -f ../../DockerFile -t server/bomberman:1.0.0 ../../', (process.platform == 'win32') ? self._env : null, function() {
				setTimeout(function() {
					cb();
				}, 1000);
			}, true));
		};

		if (process.platform == 'win32') {
			return (this.bash('./server/start.sh', null, function() {
				run();
			}, false));
		} else {
			run();
		}
	}
};

module.exports = new obj();