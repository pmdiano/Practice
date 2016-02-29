function doAjax(url, query, callback, reqtype, getxml) {
    var myreq = new XMLHttpRequest();
    myreq.onreadystatechange = function() {
        if (myreq.readyState == 4 && myreq.status == 200) {
            var item = myreq.responseText;
            if (getxml == 1) item = myreq.responseXML;
            eval(callback + '(item)');
        }
    }
    if (reqtype.toUpperCase() == "POST") {
        requestPOST(url, query, myreq);
    } else {
        requestGET(url, query, myreq);
    }
}

function requestGET(url, query, req) {
    var myrandom = parseInt(Math.random() * 99999999);
    if (query == '') {
        var callurl = url + '?rand=' + myrandom;
    } else {
        var callurl = url + '?' + query + '&rand=' + myrandom;
    }
    req.open("GET", callurl, true);
    req.send(null);
}

function requestPOST(url, query, req) {
    req.open("POST", url, true);
    req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    req.send(query);
}