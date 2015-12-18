window.onload = function() {
    document.onkeydown = function(e) {
        document.getElementById("div1").innerHTML += String.fromCharCode(e.keyCode);
    }
}
