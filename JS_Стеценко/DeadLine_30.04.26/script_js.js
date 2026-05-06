let while_first_number = prompt("While.1] Введите число, для отображения этого кол-ва '#'")

function while_first_answ(){
    let a = 0, b = "";
    while (a != while_first_number){
        b += "#";
        a ++;
    }
    return b;
}

document.getElementById("while_1").textContent = `While.1] ${while_first_answ()}`

// 2

let while_second_number = prompt("While.2] Введите число для отсчета до нуля");

function while_second_answ(){
    let a = while_second_number, b = "";
    while(a >= 0) {
        b += `${a} `;
        a--;
    }
    return b;
}

document.getElementById("while_2").textContent = `While.2] ${while_second_answ()}`;

// 3

let while_third_a = prompt("While.3] Введите число");
let while_third_b = prompt(`While.3] Введите степень для числа ${while_third_a}`);

function while_third_answ(){
    let a = 1, b = while_third_a;
    while(a != while_third_b){
        b = b * while_third_a;        
        a++;
    }
    return b;
}

document.getElementById("while_3").textContent = `While.3] ${while_third_answ()}`;

// 4

let while_firth_a = prompt("While.4] Введите число A");
let while_firth_b = prompt("While.4] Введите число B");

function while_firth_answ(){
    function min(){
        if (while_firth_a > while_firth_b) {return while_firth_b}
        return while_firth_a;
    } // поиск числа до какого момента просто искать общие делители.
    
    function max(){
        if (while_firth_a > min()) {return while_firth_a;}
        else {return while_firth_b;}
    }
    let a = 1, b = "";
    while (a != min()){
        if (max() % a == 0 && min() % a == 0) {b += `${a} `;}
        a++;
    }
    return b;
}// иногда мой разум отключается и мозг сам пишет решения, стоит только очки одеть... :D

document.getElementById("while_4").textContent = `While.4] общие делители 
${while_firth_a} и ${while_firth_b}= ${while_firth_answ()}`;

// 5

let while_five_number_a = prompt("Введите число, которое будут возводить в факториал:");

function while_five_answ(){
    let a = 1, b = 1;
    while (a <= while_five_number_a){
        b *= a;
        a ++;
    }
    return b;
}

document.getElementById("while_5").textContent = `While.5] факториал ${while_five_number_a} = ${while_five_answ()}`;


// Do While
// 1
let do_while_first;
do {
    do_while_first = prompt(
        do_while_first === undefined
            ? "Решите задачу: '2 + 2 * 2'. Чему будет равно ?"
            : "Неверный ответ. Решайте: '2 + 2 * 2'."
    );
} while (do_while_first != 6);

document.getElementById("do_while_1").textContent = `DoWhile.1] Ответ: 6`;

// 2 
let do_while_second_OH = 1000;
do{
    do_while_second_OH = do_while_second_OH / 2;
} while (do_while_second_OH >= 50)

document.getElementById("do_while_2").textContent = `DoWhile.2] (1000/2...) Получилось число: ${do_while_second_OH}`;


// For
// 1 

let for_first_number = prompt("Введите число для нахождения его кратных чисел [1 - 100]");

function for_first_answ(){
    let b = "";
    for (let a = 1; a < for_first_number; a ++){
        if (for_first_number % a == 0) {b += `${a} `}
    }
    return b;
}
document.getElementById("for_1").textContent = `For.1] Все кратные ${for_first_number}: ${for_first_answ()}`

// 2

let for_second_min = prompt("For.2] Введите минимальное значение диапазона");
let for_second_max = prompt("For.2] Введите максимальное значение диапазона");

function for_second_answ(){
    let b = "", c = 0;
    for (let a = for_second_min; a < for_second_max; a++){
        c++;
        if (c == 4){
            c = 0;
            b += `${a} `;
        }
    }
    return b;
}
document.getElementById("for_2").textContent = `For.2] Каждый четвертый эллемент диапазона
${for_second_min} - ${for_second_max}: ${for_second_answ()}`;

// 3

let for_third_number = prompt("Введите число для проверки 'Простое ли оно ?'");

function for_third_answ(){
    if (for_third_number <= 1) {return `Число ${for_third_number} - не простое.`}
    let b = "";
    for (let a = 2; a < for_third_number; a++){
        if (for_third_number % a == 0){ b += `${a} `; if (a != 1 || a != for_third_number) {return `Ужас, кажется это число не простое, т.к. поделилось на ${a}`} else {continue;}}
    }
    return `Да все норм, это простое число.`;
}
document.getElementById("for_3").textContent = `For.3] ${for_third_answ()}`;