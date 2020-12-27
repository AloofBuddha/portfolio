# Summary
A simple RESTful server and React client written in JavaScript/Node.js. I included this to illustrate the basic skills I use in my profeesion as a web developer. 

# File strucure

- server/src/db.sjon -  a json object representing a classroom of students
- server/src/index.js - creates the server and listens on port 8080 for API calls
- server/src/router.js - GET endpoints for various sources of data
- client/src/index.js - renders our App component to the DOM
- client/src/App.js - renders the full classroom information and fetches data from the API on mount
- client/src/components/Students.js - renders list of Students, fetches data, and handles pagination. This all could have been included in App.js directly but wanted to illustrate composability of React components

## Running

### server
```sh
cd server
npm install
npm start
```
serves API on `http://localhost:8080`

Accepts GET routes
* `/classroom`
* `/teacher`
* `/students`
* `/average`

### client
```sh
cd client
npm install
npm start
```

Serves front-end on `http://localhost:3000`