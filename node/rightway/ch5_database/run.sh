#!/bin/bash
./dbcli.js PUT books
node --harmony import-books.js
./make-view.js
./dbcli.js GET 'books/_design/books/_view/by_author?group=true'
