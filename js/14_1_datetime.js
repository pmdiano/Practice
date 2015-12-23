function telltime() {
    var out = "";
    var now = new Date();
    out += "<br />Date: " + now.getDate();
    out += "<br />Month: " + now.getMonth();
    out += "<br />Year: " + now.getFullYear();
    out += "<br />Hours: " + now.getHours();
    out += "<br />Minutes: " + now.getMinutes();
    out += "<br />Seconds: " + now.getSeconds();
    document.getElementById("div1").innerHTML = out;
}

function addContent() {
    var before = document.body.innerHTML;
    var after = "The current date and time are:<br />" + 
                "<div id='div1'></div>" + 
                "<input id='btn1' type='button' value='Refresh' />" +
                before;
    document.body.innerHTML = after;
}

window.onload = function() {
    addContent();
    telltime();
    document.getElementById("btn1").onclick = function() {
        location.reload();
    }
}
