/**
 * Basic server
 */

const
  fs = require('fs'),
  path = require('path'),
  express = require('express'),
  bodyParser = require('body-parser'),
  app = express(),
  COMMENTS_FILE = path.join(__dirname, 'comments.json')
  ensureFile = function (file, res, callback) {
    fs.readFile(file, function (err, data) {
      if (err) {
        res.status(404).json({
          error: "service_unavailable",
          reason: "file_read_error"
        });
      } else {
        callback(data);
      }
    })
  };

app.set('port', (process.env.PORT || 3000));

app.use('/', express.static(path.join(__dirname, 'public')));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

app.use(function (req, res, next) {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Cache-Control', 'no-cache');
  next();
});

app.get('/api/comments', function (req, res) {
  ensureFile(COMMENTS_FILE, res, function (data) {
    res.json(JSON.parse(data));
  });
});

app.post('/api/comments', function (req, res) {
  ensureFile(COMMENTS_FILE, res, function (data) {
    var now = JSON.parse(data);
    if (now.comments == null) {
      now.comments = [];
    }
    var newComment = {
      id: Date.now(),
      author: req.body.author,
      text: req.body.text
    };
    now.comments.push(newComment);

    fs.writeFile(COMMENTS_FILE, JSON.stringify(now, null, 4), function (err) {
      if (err) {
        console.error(err);
        res.status(403).json({
          error: "service_unavailable",
          reason: "file_write_error"
        });
      } else {
        res.json(now);
      }
    });
  });
});

app.listen(app.get('port'), function() {
  console.log('Server started: http://localhost:' + app.get('port') + '/');
});
