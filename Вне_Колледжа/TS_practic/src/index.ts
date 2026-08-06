/* function greet(name: string): string {
  return `1 Hello, ${name}!`;
}

console.log(greet("1"));

function test2 (i?: number | string | boolean){
    if (typeof i === "number"){
        return `It's number: ${i}`;
    }
    if (typeof i == "boolean"){
        return `It's boolean: ${i}`;
    }
    if (i == null){
        return `Зачем пустая ? Ну i: ${i}`;
    }
    else {
        return `Something else: ${i}`;
    }
}

console.log(test2(2))
console.log(test2(true))
console.log(test2()) */


// Generics Base
/* function wrap<T>(i: T): {i:T} {
    return {i};
}
// Читается как <T> - объявление самого generics типа данных. i: T - соответствует типу данных T(Generics), "...: {i:T} {..." - функция возвращает тоже значение T
// T тип данных Generics сам определяет из контекста что и получит
const res = wrap("MEOW:3")
console.log(res.i.toUpperCase());


// Generics практика на примерах
// 1

function getFirstElement<T>(arr : T[]): T | undefined {
    return arr.length > 0? arr[0]: undefined;
}

console.log(getFirstElement([1,2,3]));
console.log(getFirstElement(['a','b','c']));
console.log(getFirstElement([true,2,'a']));*/

// 2
/* function secondMakePair<T, Y>(first : T, second : Y) : {first: T, second: Y} {
    return {first, second};
}

let dsa = 'DSA';

const pair = secondMakePair(42, `dsa ${dsa}`);
console.log(`1) Генерик: ${typeof pair.first}\n2) Генерик: ${typeof pair.second}`); */


function getProperty<T, K extends keyof T>(obj: T, key: K): T[K] {
    return obj[key];
}

const user = { name: 'Alice', age: 30 };
const name = getProperty(user, 'name'); // тип string
console.log(name);