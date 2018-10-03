let Repeater = require('function-repeater');
let X = require('../src/index');

console.log(X.Utility.SendKeysState);

let keyCatcher = new X.KeyCatcher();
keyCatcher.begin();

keyCatcher.setCallback((down, code) => {
    console.log(down, code);
    return false;
});

new Repeater(() => {
    keyCatcher.update();
}, 20, true);

let window = new X.Window("elephant");

window.makeWindow();
window.setGeometry(100, 100, 250, 60);
window.setLines(3, 20);
window.show();
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");
window.setLine(2, "too many lines");

window.setSystemTrayCallback(() => {
    console.log('whats up')
});

let increment = new Repeater(
    (_, i) => {
        window.setLine(0, i);
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