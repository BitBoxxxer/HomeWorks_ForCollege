//#region # 1 ПРОСТО БАЗА

/* import http from 'node:http';

const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/plain' });
  res.end('Hello, World!\n');
});

server.listen(3000, () => {
  console.log('Server running at http://localhost:3000/');
}); */

//#region # 2 GET
/* import http from "node:http";

let products = [
  { id: 1, name: "Клавиатура", price: 12000 },
  { id: 2, name: "Мышь", price: 4000 },
];

const server = http.createServer(async (req, res) => {
  res.setHeader("Content-Type", "application/json; charset=utf-8");

  if (req.method === "GET" && req.url === "/products") {
    res.end(JSON.stringify(products));
    return;
  }
});

server.listen(3000, () => {
  console.log("Сервер запущен");
}); */



//#region 3 Конечный код

import { error } from "node:console";
import http from "node:http";

let products = [
  { id: 1, name: "РљР»Р°РІРёР°С‚СѓСЂР°", price: 12000 },
  { id: 2, name: "РњС‹С€СЊ", price: 4000 },
];

const server = http.createServer(async (req, res) => {
  res.setHeader("Content-Type", "application/json; charset=utf-8");

  if (req.method === "GET" && req.url === "/products") {
    res.end(JSON.stringify(products));
    return;
  }
  if (req.method === "POST" && req.url === "/products")
    try {
      let body = "";
      for await (const chunk of req) {
        body += chunk;
      }
      const data = JSON.parse(body);

      if (
        typeof data.name !== "string" ||
        !data.name.trim() ||
        typeof data.price !== "number" ||
        !Number.isFinite(data.price) ||
        data.price < 0
      ) {
        res.statusCode = 400;
        res.end(JSON.stringify({ error: "РќРµРєРѕСЂСЂРµРєС‚РЅС‹Рµ РґР°РЅРЅС‹Рµ С‚РѕРІР°СЂР°" }));
        return;
      }
      const newProduct = {
        id: Math.max(0, ...products.map((p) => p.id)) + 1,
        name: data.name.trim(),
        price: data.price,
      };

      products.push(newProduct);
      res.statusCode = 201;
      res.end(JSON.stringify(newProduct));
      return;
    } catch {
      res.statusCode = 400;
      res.end(
        JSON.stringify({
          error: "РќРµРІРµСЂРЅС‹Рµ РґР°РЅРЅС‹Рµ",
        }),
      );
    }

  res.statusCode = 404;
  res.end(
    JSON.stringify({
      error: "РњР°СЂС€СЂСѓС‚ РЅРµ РЅР°Р№РґРµРЅ",
    }),
  );
});

server.listen(3000, () => {
  console.log("РЎРµСЂРІРµСЂ Р·Р°РїСѓС‰РµРЅ");
});