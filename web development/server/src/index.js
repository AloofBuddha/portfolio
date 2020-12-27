import express from 'express';

import router from './router';

const app = express();
const port = 8080; // default port to listen

// set header for CORS request from our server
app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  next();
});

app.use(router);

// start the Express server
app.listen(port, () => {
  console.log(`server started at http://localhost:${port}`);
});
