// 1

let userName = "Ronaldo";


// 2
console.log("Привет, это двойные кавычки. Имя: " + userName);
console.log('Это одиночные кавычки. Имя:' + userName);
console.log(`Это одиночные изогнутые кавычки. Имя: ${userName}`);


// 3
let price = "150.5";
console.log(parseFloat(price) - 50);
console.log(parseFloat(price) + 10);

let result = parseFloat(price) / 2;
console.log(Math.trunc(result));