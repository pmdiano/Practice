function outer() {
  inner();
}

function inner() {
  alert(arguments.callee.caller);
}

outer();
