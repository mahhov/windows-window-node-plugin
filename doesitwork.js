let {Window} = require('./');

let sleep = ms => new Promise(resolve => setTimeout(resolve, ms));

let window = new Window();
window.makeWindow();
console.log('made returned')
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
}, 1);

loop(() => {
    window.update();
}, 1);
