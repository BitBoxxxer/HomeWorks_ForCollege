import http from "node:http";
import fs from "node:fs";

const FILE = new URL("./products.json", import.meta.url);

let products = [
    { id: 1, name: "Product 1", price: 10.99, category: "Electronics", quantity: 100 },
    { id: 2, name: "Product 2", price: 19.99, category: "Books", quantity: 50 },
    { id: 3, name: "Product 3", price: 5.99, category: "Clothing", quantity: 200 },
    { id: 4, name: "Product 4", price: 29.99, category: "Home & Kitchen", quantity: 75 },
    { id: 5, name: "Product 5", price: 15.99, category: "Sports", quantity: 120 },
    { id: 6, name: "Product 6", price: 9.99, category: "Toys", quantity: 80 },
    { id: 7, name: "Product 7", price: 49.99, category: "Beauty", quantity: 60 },
    { id: 8, name: "Product 8", price: 12.99, category: "Electronics", quantity: 90 },
    { id: 9, name: "Product 9", price: 7.99, category: "Books", quantity: 150 },
    { id: 10, name: "Product 10", price: 24.99, category: "Clothing", quantity: 110 }
]; // vsc помог заполнить инфу для товара

function saveProducts() { fs.writeFileSync(FILE, JSON.stringify(products, null, 2), "utf-8"); }

if (fs.existsSync(FILE)) {
  try { products = JSON.parse(fs.readFileSync(FILE, "utf-8")); } catch { console.error("file err: ", FILE); }
} else { saveProducts(); }

async function readBody(req) {
  let data = "";
  try { for await (const chunk of req) { data += chunk; } } catch { throw new Error("Ошибка чтения запроса"); }

  let parsed;
  try { parsed = JSON.parse(data); } catch { throw new Error("Некорректный JSON"); }

  if (parsed === null || typeof parsed !== "object" || Array.isArray(parsed)) { throw new Error("Тело запроса должно быть JSON-объектом"); }
  return parsed;
}

function validateProduct(p) {
  if (typeof p.name !== "string" || p.name.trim() === "") { return "Название должно быть непустой строкой"; }
  if (typeof p.category !== "string" || p.category.trim() === "") { return "Категория должна быть непустой строкой"; }
  if (typeof p.price !== "number" || !Number.isFinite(p.price) || p.price < 0) { return "Цена должна быть числом не меньше 0"; }
  if (!Number.isInteger(p.quantity) || p.quantity < 0) { return "Количество должно быть целым числом не меньше 0"; }
  return null;
}

const server = http.createServer(async (req, res) => {
  res.setHeader("Content-Type", "application/json; charset=utf-8");

  try {
    const url = new URL(req.url, "http://localhost:3000");
    const parts = url.pathname.split("/");
    const method = req.method;

    // GET /products
    if (method === "GET" && url.pathname === "/products") {
      res.end(JSON.stringify(products));
      return;
    }

    // GET /products/search?name=
    if (method === "GET" && url.pathname === "/products/search") {
      const name = (url.searchParams.get("name") || "").trim().toLowerCase();
      if (name === "") { res.statusCode = 400; res.end(JSON.stringify({ message: "Параметр name обязателен" })); return; }
      const found = products.filter((p) => p.name.toLowerCase().includes(name));
      res.end(JSON.stringify(found));
      return;
    }

    // GET /stats
    if (method === "GET" && url.pathname === "/stats") {
      const total = products.reduce((sum, p) => sum + p.price * p.quantity, 0);
      const mostExpensive = products.length ? products.reduce((max, p) => (p.price > max.price ? p : max)) : null;
      res.end(JSON.stringify({ count: products.length, totalValue: Number(total.toFixed(2)), mostExpensive }));
      return;
    }

    // POST /products
    if (method === "POST" && url.pathname === "/products") {
      const body = await readBody(req);
      const error = validateProduct(body);
      if (error) { res.statusCode = 400; res.end(JSON.stringify({ message: error })); return; }

      const newId = products.length ? Math.max(...products.map((p) => p.id)) + 1 : 1;
      const product = { id: newId, name: body.name.trim(), price: body.price, category: body.category.trim(), quantity: body.quantity };
      products.push(product);
      saveProducts();
      res.statusCode = 201;
      res.end(JSON.stringify(product));
      return;
    }

    // /products/:id (GET, PUT, DELETE)
    if (parts[1] === "products" && parts.length === 3) {
      if (!/^\d+$/.test(parts[2])) { res.statusCode = 400; res.end(JSON.stringify({ message: "ID должен быть целым положительным числом" })); return; }
      const id = Number(parts[2]);
      const index = products.findIndex((p) => p.id === id);
      if (index === -1) { res.statusCode = 404; res.end(JSON.stringify({ message: "Товар не найден" })); return; }

      if (method === "GET") {
        res.end(JSON.stringify(products[index]));
        return;
      }

      if (method === "PUT") {
        const body = await readBody(req);
        const updated = { ...products[index], ...body, id }; // id менять нельзя
        const error = validateProduct(updated);
        if (error) { res.statusCode = 400; res.end(JSON.stringify({ message: error })); return; }

        updated.name = updated.name.trim();
        updated.category = updated.category.trim();
        products[index] = updated;
        saveProducts();
        res.end(JSON.stringify(updated));
        return;
      }

      if (method === "DELETE") {
        const [removed] = products.splice(index, 1);
        saveProducts();
        res.end(JSON.stringify(removed));
        return;
      }
    }

    // Неизвестный маршрут
    res.statusCode = 404;
    res.end(JSON.stringify({ message: "Список(products) не найден [indes.js, const server]" }));
  } catch (e) {
    if (e.message === "Некорректный JSON" || e.message === "Тело запроса должно быть JSON-объектом" || e.message === "Ошибка чтения запроса") {
      res.statusCode = 400;
      res.end(JSON.stringify({ message: e.message }));
      return;
    }
    res.statusCode = 500;
    res.end(JSON.stringify({ message: "Внутренняя ошибка сервера" }));
  }
});

server.listen(3000, () => {
  console.log("сервер запущен на порту 3000. http://localhost:3000/products");
});