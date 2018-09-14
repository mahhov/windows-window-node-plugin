let {Window} = require('../src/index');

class Tooltip {
    constructor() {
        this.window = new Window();
        this.window.makeWindow();
        this.window.setGeometry(100, 100, 250, 40);
        this.window.setLines(2, 20);
    }

    show(line0, line1, duration) {
        this.window.setLine(0, line0);
        this.window.setLine(1, line1);
        this.window.show();
        setTimeout(() => this.window.update(), 100);
        this.window.update();
        setTimeout(() => this.window.hide(), duration);
    }

    hide() {
        this.window.hide();
        // this.window.update();
    }
}

tt = new Tooltip();
tt.show('hi', 'bye', 1000);
