"use strict";
const
  fs = require('fs'),
  spawn = require('child_process').spawn;

try {
  var filename = process.argv[2];
  var procname = process.argv[3];
  var procargs = process.argv.slice(4);

  if (!filename) {
    throw Error("file to watch not specified");
  }
  if (!procname) {
    throw Error("watcher action not specified");
  }

  fs.watch(filename, function(){
    var proc = spawn(procname, procargs);
    proc.stdout.pipe(process.stdout);
    proc.stderr.pipe(process.stderr);
  });

  console.log("Watching " + filename + " for changes...");
} catch (err) {
  console.log("Error: " + err.message);
}
