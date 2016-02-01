'use strict';
const
  express = require('express'),
  session = require('express-session'),
  RedisStore = require('connect-redis')(session),
  morgan = require('morgan'),
  cookieParser = require('cookie-parser'),
  redisClient = require('redis').createClient(),
  app = express();

app.use(morgan('combined'));
app.use(cookieParser());
app.use(session({
  secret: 'unguessable',
  store: new RedisStore({
    client: redisClient
  }),
  resave: true,
  saveUninitialized: true
}));

app.get('/api/:name', function(req, res) {
  res.status(200).json({ "hello": req.params.name });
});

app.listen(3000, function(){
  console.log("ready captain.");
});
