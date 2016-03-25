/**
 * ES6 Promise
 * http://www.cnblogs.com/lvdabao/p/es6-promise-1.html
 */

/**
 * Basic usage of Promise with resolve
 */

var waitUntil = (millilseconds, msg, exec) => {
  setTimeout(() => {
    console.log('\n现在是第' + millilseconds/1000 +'秒，开始' + msg);
    exec();
  }, millilseconds);
};

function runAsync1(){
    var p = new Promise(function(resolve, reject){
        //做一些异步操作
        setTimeout(function(){
            console.log('异步任务1执行完成');
            resolve('随便什么数据1');
        }, 1000);
    });
    return p;            
}
function runAsync2(){
    var p = new Promise(function(resolve, reject){
        //做一些异步操作
        setTimeout(function(){
            console.log('异步任务2执行完成');
            resolve('随便什么数据2');
        }, 2000);
    });
    return p;            
}
function runAsync3(){
    var p = new Promise(function(resolve, reject){
        //做一些异步操作
        setTimeout(function(){
            console.log('异步任务3执行完成');
            resolve('随便什么数据3');
        }, 2000);
    });
    return p;            
}

runAsync1()
.then(function(data){
    console.log(data);
    return runAsync2();
})
.then(function(data){
    console.log(data);
    return '直接返回数据';
})
.then(function(data){
    console.log(data);
});


/**
 * Usage with reject
 */

function getNumber(){
    var p = new Promise(function(resolve, reject){
        //做一些异步操作
        setTimeout(function(){
            var num = Math.ceil(Math.random()*10); //生成1-10的随机数
            if(num<=5){
                resolve(num);
            }
            else{
                reject('数字太大了');
            }
        }, 1000);
    });
    return p;            
}

waitUntil(4000, 'reject用例', () => {
  getNumber()
  .then(
      function(data){
          console.log('resolved');
          console.log(data);
      }, 
      function(reason, data){
          console.log('rejected');
          console.log(reason);
      }
  );
});


/**
 * Usage with catch
 */

waitUntil(6000, 'catch用例', () => {
  getNumber()
  .then(function(data){
      console.log('resolved');
      console.log(data);
      console.log(somedata); //此处的somedata未定义
  })
  .catch(function(reason){
      console.log('rejected');
      console.log(reason);
  });  
});


/**
 * Usage with Promise.all
 * 这个没有用上面的waitUntil() helper函数
 */

(() => {
  var p = new Promise(function(resolve, reject){
    setTimeout(() => {
      resolve('传给下一个');
    }, 8000);
  });
  return p;
})()
.then((data) => {
    console.log('\n接收了：' + data + '\n现在是第8秒，开始Promise.all()');
    Promise.all([runAsync1(), runAsync2(), runAsync3()])
    .then((results) => {
      console.log(results);
    });
  }
);


/**
 * Usage with Promise.race()
 */

waitUntil(12000, 'Promise.race()用例', () => {
  Promise
  .race([runAsync1(), runAsync2(), runAsync3()])
  .then((results) => {
    console.log(results);
  });
});
