'use strict';
const
  cluster = require('cluster'),
  zmq = require('zmq');

if (cluster.isMaster) {

  let
    pusher = zmq.socket('push').bind('ipc://master-pusher.ipc'),
    puller = zmq.socket('pull').bind('ipc://master-puller.ipc'),
    ready_workers = 0,
    total_workers = 3,
    message_counts = 12,
    sendWork = () => {
      for (let i = 0; i < message_counts; ++i) {
        pusher.send(JSON.stringify({
          id: i
        }));
      }
    };

  puller.on('message', (data) => {
    let message = JSON.parse(data);
    if (message.ready) {
      console.log('Worker ' + message.wid + ' is ready.');
      ready_workers += 1;
      if (ready_workers === total_workers) {
        sendWork();
      }
    } else if (message.result) {
      console.log('Worker ' + message.wid + ' has result: ' + message.msg);
    }
  });

  cluster.on('online', (worker) => {
    console.log('Worker ' + worker.process.pid + ' is online.');
  });

  // spin up the workers
  for (let i = 0; i < total_workers; ++i) {
    cluster.fork();
  }

} else {

  let
    puller = zmq.socket('pull').connect('ipc://master-pusher.ipc'),
    pusher = zmq.socket('push').connect('ipc://master-puller.ipc');

  puller.on('message', (data) => {
    let work = JSON.parse(data);
    console.log('Worker ' + process.pid + ' received work #' + work.id);
    setTimeout(() => {
      pusher.send(JSON.stringify({
        result: true,
        msg: 'Hi!' + work.id,
        wid: process.pid
      }));
    }, 2000);
  });

  pusher.send(JSON.stringify({
    ready: true,
    wid: process.pid
  }));
}
