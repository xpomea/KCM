const http = require('http');
const fs = require('fs');

const g = 5n;
const p = 23n;
const a = BigInt(Math.floor(Math.random() * 10) + 1);
const A = g ** a % p;

let clientKey = null;

const server = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    fs.createReadStream('index.html').pipe(res);
  }

  else if (req.method === 'GET' && req.url === '/params') {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({
      g: g.toString(),
      p: p.toString(),
      A: A.toString()
    }));
  }

  else if (req.method === 'POST' && req.url === '/exchange') {
    let body = '';
    req.on('data', chunk => body += chunk);
    req.on('end', () => {
      const { B } = JSON.parse(body);
      clientKey = BigInt(B);
      const shared = clientKey ** a % p;
      console.log('Shared key (server):', shared.toString());
      res.writeHead(200);
      res.end();
    });
  }

  else {
    res.writeHead(404);
    res.end();
  }
});

server.listen(8080, () => {
  console.log('Server running at http://localhost:8080');
});
