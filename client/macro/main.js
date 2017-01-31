var robot = require("robotjs");

var sleep = function(ms) {
    var waitTill = new Date(new Date().getTime() + ms);
    while (waitTill > new Date());
};

setTimeout(function() {
    var delay = 20;
    robot.mouseClick();
    for (var x = 0; x < 10; x++) {
        sleep(delay / 2);
        for (var y = 0; y < 10; y++) {
            robot.keyTap((x % 2 == 1) ? 'left' : 'right');
            sleep(delay);
            robot.keyTap('space');
            sleep(delay);
        }
        robot.keyTap('down');
        sleep(delay);
        robot.keyTap('space');
        sleep(delay / 2);
    }
}, 2000);