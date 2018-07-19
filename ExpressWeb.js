const express = require("express");
const bodyparser = require("body-parser");
const app = express();
//app.use(bodyParser.json());
//app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", function(req, res){
  res.send("Hello, World!");
  console.log(req.body);
});

app.listen(8080);
console.log("Server ready...")
