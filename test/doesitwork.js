let Repeater = require('function-repeater');
let {Window} = require('../src/index');

let window = new Window();
window.makeWindow();
window.setGeometry(100, 100, 250, 40);
window.setLines(2, 20);
window.show();
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");

let increment = new Repeater(
    (_, i) => {
        window.setLine(0, i);
        window.setLine(1, Window.getClipboardText());
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

// todo
// makeWindow to support window paramters
// more layout elements and flexibility
