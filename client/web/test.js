var a = function(id) {
    var s = require('net').Socket();
    s.connect(980, '127.0.0.1');

    if (id == 0) {
        setTimeout(function() {
            s.end();
        }, 5000);
    }

    s.on('data', function(d) {
	    console.log('--', d.toString());
    });

    s.on('connect', function() {
	    console.log('connected');
        s.write(id + '_is_id\n', function(e, r) {
            console.log('send msg', e, r);
        });
    });

    s.on('close', function() {
	    console.log('closed');
	    //setTimeout(a, 5000);
    });

    s.on('error', function(e) {
	    console.log('e', e);
    });
};
for (var i = 0; i < 2; i++) {
    a(i);
}
