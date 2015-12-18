function addEventHandler(element, eventType, handlerFunction) {
    element.addEventListener(eventType, handlerFunction, false);
}

function removeEventHandler(element, eventType, handlerFunction) {
    element.removeEventListener(eventType, handlerFunction, false);
}

function appendText(e) {
    var element = e.target;
    document.getElementById("div1").innerHTML += element.id + "<br/>";
}

function removeOnClickA() {
    removeEventHandler(document.getElementById('buttonA'), 'click', appendText);
}

function removeOnClickB() {
    removeEventHandler(document.getElementById('buttonB'), 'click', appendText);
}

function reset() {
    addEventHandler(document.getElementById('buttonA'), 'click', appendText);
    addEventHandler(document.getElementById('buttonB'), 'click', appendText);
}

window.onload = function() {
    addEventHandler(document.getElementById('button-a'), 'click', removeOnClickA);
    addEventHandler(document.getElementById('button-b'), 'click', removeOnClickB);
    addEventHandler(document.getElementById('reset'), 'click', reset);
    addEventHandler(document.getElementById('reset'), 'dblclick', ()=>{document.getElementById('div1').innerHTML = "";});
    reset();
}
