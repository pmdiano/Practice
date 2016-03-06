global.name = "Global";

var object = {
    name : "My object",

    getName: function(){
        return this.name;
    }
};

var log = function(msg){
    console.log(msg);
}

log(object.getName());      // "My object"
log((object.getName)());    // "My object"
log((object.getName = object.getName)());   // "Gloabl" - 非严格模式下
