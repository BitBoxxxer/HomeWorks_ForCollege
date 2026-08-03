"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function greet(name) {
    return `1 Hello, ${name}!`;
}
console.log(greet("1"));
function test2(i) {
    if (typeof i === "number") {
        return `It's number: ${i}`;
    }
    if (typeof i == "boolean") {
        return `It's boolean: ${i}`;
    }
    if (typeof i == null) {
        return `Зачем пустая ? Ну i: ${i}`;
    }
    else {
        return `Something else: ${i}`;
    }
}
console.log(test2(2));
console.log(test2(true));
console.log(test2());
//# sourceMappingURL=index.js.map