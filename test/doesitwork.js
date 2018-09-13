let {Window} = require('../src/index');

let sleep = ms => new Promise(resolve => setTimeout(resolve, ms));

let window = new Window();
window.makeWindow();
window.setGeometry(100, 100, 250, 40);
window.setLines(2, 20);
window.show();
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");

let loop = async (handler, ms) => {
    while (true) {
        handler();
        await sleep(ms);
    }
};

let i = 0;
loop(() => {
    window.setLine(1, "" + i++);
}, 1000);

loop(() => {
    window.update();
    console.log(window.hasWindow)
}, 5);

// todo
// makeWindow to support window paramters
// more layout elements and flexibility
// stop when window closed
