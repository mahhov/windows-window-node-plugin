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
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");
window.setLine(2, "too many lines");

window.setClipboardCallback(a => console.log('cliboard', a));

window.setSystemTrayCallback(() => console.log('sys tray'));

window.setKeyCallback(key => console.log('key', key));

window.setFocusCallback(focus => console.log('focus', focus));

let increment = new Repeater(
    (_, i) => {
        // window.setLine(0, i);
        window.setLine(1, X.Utility.getClipboardText());
    },
    1000, true);

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