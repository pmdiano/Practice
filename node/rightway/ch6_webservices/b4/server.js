#!/usr/bin/env node --harmony
/***
 * Excerpted from "Node.js the Right Way",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jwnode for more book information.
***/
/**
 * I also made some changes such that it works with Express 4.0+
 * and change from passport-google (deprecated) to passport-google-oauth
 */
'use strict';
const
  
  log = require('npmlog'),
  request = require('request'),
  
  express = require('express'),
  session = require('express-session'),
  morgan = require('morgan'),
  passport = require('passport'),
  cookieParser = require('cookie-parser'),
  ejson = require('express-json'),
  app = express(),
  
  redisClient = require('redis').createClient(),
  RedisStore = require('connect-redis')(session),
  
  GoogleStrategy = require('passport-google-oauth').OAuth2Strategy,
  GOOGLE_CLIENT_ID = "834935772635-ngfpqhkj2m17ohofoqdi3rm82bkbqma8.apps.googleusercontent.com",
  GOOGLE_CLIENT_SECRET = "RbhAH7EKBTNBTfDpwAg_G0-_";

redisClient
  .on('ready', function() { log.info('REDIS', 'ready'); })
  .on('error', function(err) { log.error('REDIS', err.message); });


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
app.use(passport.initialize());
app.use(passport.session());
app.use(express.static(__dirname + '/static'));
app.use(express.static(__dirname + '/bower_components'));


passport.serializeUser(function(user, done) {
  done(null, user.identifier);
});
passport.deserializeUser(function(id, done) {
  done(null, { identifier: id });
});
passport.use(new GoogleStrategy({
    clientID: GOOGLE_CLIENT_ID,
    clientSecret: GOOGLE_CLIENT_SECRET,
    callbackURL: 'http://localhost:3000/auth/google/return',
    passReqToCallback:true
  },
  function (request, accessToken, refreshToken, profile, done) {
    profile.identifier = profile.id;
    return done(null, profile);
  }
));

const config = {
  bookdb: 'http://localhost:5984/books/',
  b4db: 'http://localhost:5984/b4/'
};
require('./lib/book-search.js')(config, app);
require('./lib/field-search.js')(config, app);
require('./lib/bundle.js')(config, app);

app.get('/auth/google/:return?',
  passport.authenticate('google', { successRedirect: '/', scope: ['profile', 'email'] })
);
app.get('/auth/logout', function(req, res){
  req.logout();
  res.redirect('/');
});

const authed = function(req, res, next) {
  if (req.isAuthenticated()) {
    return next();
  } else if (redisClient.ready) {
    res.status(403).json({
      error: "forbidden",
      reason: "not_authenticated"
    });
  } else {
    res.status(503).json({
      error: "service_unavailable",
      reason: "authentication_unavailable"
    });
  }
};

app.get('/api/user', authed, function(req, res){
  res.json(req.user);
});

app.get('/api/user/bundles', authed, function(req, res) {
  let userURL = config.b4db + encodeURIComponent(req.user.identifier);
  request(userURL, function(err, couchRes, body) {
    if (err) {
      res.status(502).json({ error: "bad_gateway", reason: err.code });
    } else if (couchRes.statusCode === 200) {
      res.json(JSON.parse(body).bundles || {});
    } else {
      res.send(couchRes.statusCode, body);
    }
  });
});

app.put('/api/user/bundles', [authed, ejson()], function(req, res) {
  let userURL = config.b4db + encodeURIComponent(req.user.identifier);
  request(userURL, function(err, couchRes, body) {
    if (err) {
      res.status(502).json({ error: "bad_gateway", reason: err.code });
    } else if (couchRes.statusCode === 200) {
      let user = JSON.parse(body);
      user.bundles = req.body;
      request.put({ url: userURL, json: user }).pipe(res);
    } else if (couchRes.statusCode === 404) {
      let user = { bundles: req.body };
      request.put({ url: userURL,  json: user }).pipe(res);
    } else {
      res.send(couchRes.statusCode, body);
    }
  });
});

app.listen(3000, function(){
  console.log("ready captain.");
});

