function Person(name, age, job) {
    var o = new Object();
    o.name = name;
    o.age = age;
    o.job = job;
    o.sayName = function() {
        console.log(this.name);
    };
    return o;
}

var p1 = new Person("Nicholas", 29, "Software Engineer");
var p2 = new Person("Greg", 27, "Doctor");
p1.sayName();
p2.sayName();
console.log(p1.sayName === p2.sayName);
