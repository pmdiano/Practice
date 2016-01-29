'use strict';
const
  rdfParser = require('../lib/rdf-parser.js'),
  expectedValue = require('./pg132.json');
exports.testRDFParser = function(test) {
  rdfParser(__dirname + '/pg132.rdf', function (err, book) {
    test.expect(3);
    test.ifError(err);
    test.equal(book._id, expectedValue._id);
    test.equal(book.title, expectedValue.title);
    // test.deepEqual(book, expectedValue, "book should match expected");
    test.done();
  });
};
