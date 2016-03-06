global.name = "Global";

var object = {
    name : "My Object",

    getNameFunc : function(){
        return function(){
            return this.name;
        };
    }
};

console.log(object.getNameFunc()()); // Global - 非严格模式下；严格模式下出错
