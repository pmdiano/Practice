/**
 * POST: create
 * GET: read
 * PUT: update
 * DELETE: delete
 * 
 * The difference between POST and PUT is subtle but important.
 * If you already have the full URL for the RESTful thing you're
 * working on, then you use PUT. Otherwise, you use POST.
 * So if you're updating an existing resource, PUT is always
 * correct, but to create a new resource you use PUT only if you
 * know the full URL to where that resource will be.
 */
'use strict';
const

  request = require('request'),
  async = require('async'),
  file = require('file'),
  rdfParser = require('./lib/rdf-parser.js'),

  work = async.queue(function (path, done) {
    rdfParser(path, function (err, doc) {
      request({
        method: 'PUT',
        url: 'http://localhost:5984/books/' + doc._id,
        json: doc
      }, function (err, res, body) {
        if (err) {
          throw Error(err);
        }
        console.log(res.statusCode, body);
        done();
      });
    });
  }, 10);

console.log('beginning directory walk');
file.walk(__dirname + '/cache', function (err, dirPath, dirs, files) {
  files.forEach(function (path) {
    work.push(path);
  });
});
