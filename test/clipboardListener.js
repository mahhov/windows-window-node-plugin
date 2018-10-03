let Repeater = require('function-repeater');
let X = require('../src/index');

let window = new X.Window();

window.makeWindow();

window.beginClipboardListener();

window.setClipboardCallback(x => console.log(x));

new Repeater(() => window.update(), 0, true);

console.log('begin')