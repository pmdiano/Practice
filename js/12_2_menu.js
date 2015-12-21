function insertAfter(parent, child, target) {
    if (child.nextSibling) {
        parent.insertBefore(target, child.nextSibling);
    }
}

function makemenu() {
    var h2s = document.getElementsByTagName("h2");
    var ps = document.getElementsByTagName("p");
    var menu = document.createElement("div");
    var menuUl = document.createElement("ul");
    var menuanc = document.createElement("a");
    menuanc.setAttribute("name", "menutop");
    menu.appendChild(menuanc);
    menu.appendChild(menuUl);

    for (var i = 0; i < h2s.length; i++) {
        var itemText = h2s[i].childNodes[0].nodeValue;
        var menuLi = document.createElement("li");
        menuUl.appendChild(menuLi);

        var menuLiA = document.createElement("a");
        menuLiA = menuLi.appendChild(menuLiA);
        menuLiA.setAttribute("href", "#item" + i);

        var menuText = document.createTextNode(itemText);
        menuLiA.appendChild(menuText);

        var anc = document.createElement("a");
        anc.setAttribute("name", "item" + i);
        document.body.insertBefore(anc, h2s[i]);

        var backtotop = document.createElement("a");
        var backtotoptext = document.createTextNode("Back to Top");
        backtotop.setAttribute("href", "#menutop");
        backtotop.appendChild(backtotoptext);
        if (h2s[i+1]) {
            document.body.insertBefore(backtotop, h2s[i+1]);
        } else {
            document.body.insertBefore(backtotop, document.body.lastChild);
        }
    }
    document.body.insertBefore(menu, document.body.firstChild);
}
