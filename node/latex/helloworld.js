'use strict';
const
  spawn = require('child_process').spawn,
  pdflatex = spawn('pdflatex', ['helloworld.tex']);

pdflatex.on('exit', function (code) {
  console.log('pdflatex exited with code ' + code);
});
