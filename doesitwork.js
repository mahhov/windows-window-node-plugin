let {Window} = require('./');

let window = new Window();
window.makeWindow();
window.setGeometry(100, 100, 250, 40);
window.setLines(2, 20);
window.show();
window.setLine(0, "hi there !!");
window.setLine(1, "this is line 2");
while (window.update())
    ;
