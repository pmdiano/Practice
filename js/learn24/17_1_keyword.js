function display(content) {
    document.getElementById("displaydiv").innerHTML = content;
}

window.onload = function() {
    document.getElementById("btn1").onclick = function() {
        var url = document.getElementById("txt1").value;
        doAjax("keyword.php", "url="+url, "display", "post", 0);
    }
}
