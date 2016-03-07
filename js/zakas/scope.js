var scopeLosingExample = {
    text: "Property from lexical scope losing example",
    run: function() {
        setTimeout(function(){
            console.log(this.text);
        }, 1000);
    }
};

var scopePreservingExample = {
    text: "Property from lexical scope preserving example",
    run: function() {
        setTimeout(() => {
            console.log(this.text);
        }, 1000);
    }
};

scopeLosingExample.run();
scopePreservingExample.run();
