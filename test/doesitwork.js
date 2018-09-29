let Repeater = require('function-repeater');
let X = require('../src/index');

let keyCatcher = new X.KeyCatcher();
keyCatcher.begin();

keyCatcher.setCallback((down, code) => {
    console.log(down, code);
    return code === 32;
});

new Repeater(() => {
    keyCatcher.update();
}, 20, true);

let window = new X.Window("elephant");

window.makeWindow();
window.setGeometry(100, 100, 250, 40);
window.setLines(2, 20);
window.show();
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");

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
    console.log(X.Utility.mousePosition());
}, 100, true);