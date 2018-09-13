let {Window} = require('../src/index');

let sleep = ms => new Promise(resolve => setTimeout(resolve, ms));

let window = new Window();
window.makeWindow();
console.log('made returned');
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
    console.log('increment');
    window.setLine(1, "" + i++);
}, 1000);

loop(() => {
    console.log('update');
    window.update();
}, 5);


// auto make window
// auto param type conversion
// stop when window closed