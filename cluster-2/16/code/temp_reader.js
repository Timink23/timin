// JavaScript source code
var http = require('http');
const { SerialPort } = require('serialport')
const Readline = require('@serialport/parser-readline');

const port = new SerialPort(
{
    path: 'COM5',
    baudRate: 115200,
    autoOpen: true,
});

//var rl = readline.createInterface(
//  process.stdin, process.stdout);

port.on("open", () => {
    console.log('serial port open');
});




http.createServer(function (req, res) {
    res.write("Getting Serial Data \n");
    port.on('data', function (data) {
        res.write(data);
    })


}).listen(8080);
