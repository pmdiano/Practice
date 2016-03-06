global.name = "Global";

var object = {
    name : "My Object",

    getNameFunc : function(){
        var that = this;
        return function(){
            return that.name;
        };
    }
};

console.log(object.getNameFunc()()); // My Object
