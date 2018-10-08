let Repeater = require('function-repeater');
let X = require('../src/index');

console.log(X.Utility.SendKeysState);

let keyCatcher = new X.KeyCatcher();
keyCatcher.begin();

keyCatcher.setCallback((down, code) => {
    window.setLine(3, down + ' ' + code);
    return false;
});

new Repeater(() => {
    keyCatcher.update();
}, 20, true);

let window = new X.Window("elephant");

window.makeWindow(true);
window.setGeometry(100, 100, 250, 80);
window.setLines(4, 20);
window.show();
window.setLine(0, "hi there !!", [255, 0, 0]);
window.setLine(1, "clipboard contents");
window.setLine(2, "mouse cords");
window.setLine(3, "global key press");

window.setClipboardCallback(a => window.setLine(1, a, [0, 255, 0], [0, 0, 0]));

window.setSystemTrayCallback(() => console.log('sys tray'));

window.setKeyCallback(key => console.log('key', key));

window.setFocusCallback(focus => console.log('focus', focus));

new Repeater(
    update => {
        window.update();
        if (!window.hasWindow) {
            increment.stop();
            update.stop();
        }
    }, 5, true);

new Repeater(() => {
    window.setLine(2, X.Utility.mousePosition());
}, 100, true);