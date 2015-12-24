function showtime() {
    var now = new Date();
    var time = now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
    document.getElementById("clock").innerHTML = "Local time: " + time;
}

window.onload = function() {
    setInterval(showtime, 100);
}
