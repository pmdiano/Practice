module.exports = {
  by_author: {
    map: function (doc) {
      if ('authors' in doc) {
        // doc.authors.forEach(emit);
        emit(doc.authors);
      }
    }.toString(),
    reduce: '_count"'
  }
};
