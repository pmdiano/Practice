function createFunctions(){
    var result = new Array();

    for (var i=0; i < 10; i++){
        result[i] = function(num){
            return function(){
                return num;
            }
        }(i);
    }

    return result;
}

createFunctions().forEach((f) => {
    console.log(f());   // 0..9
});
