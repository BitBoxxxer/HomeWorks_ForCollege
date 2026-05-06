let first_number = prompt("Введите любое число: ");

function first_answ(){
    if (first_number > 0) {return `Число ${first_number} больше 0`}
    if (first_number < 0) {return `Число ${first_number} меньше 0`}
    if (first_number == 0) {return `Число ${first_number} является 0`}

}
document.getElementById("h1_1").textContent = `1] ${first_answ()}`;


// 2

let second_age = prompt("(2) Сколько вам лет ? [0-120 лет]");

function second_answ(){
    if (second_age >= 0 && second_age <= 120) {return `Возраст ${second_age} входит в диапазон [0-120]`}
    else {return `Что-то пошло не так. ${second_age} вне диапазона [0-120]`}
}
document.getElementById("h1_2").textContent = `2] ${second_answ()}`;

// 3

let third_modul = prompt("Введите любое число, чтобы найти его модуль :)");

function third_answ(){
    if (third_modul >= 0 ) {return third_modul}
    else {return third_modul * -1}
}

document.getElementById("h1_3").textContent = `3] Модуль числа ${third_modul} = ${third_answ()}`;

// 4 
// P.s. мне было лень это разбивать через массив,
// поэтому каждый компонент (час, минута, секунды)
// - запрашиваются отдельно :р

let firth_time_hour = prompt("4] Введите час: [0 - 23]");
let firth_time_minute = prompt("4] Введите минуты: [0 - 59]");
let firth_time_seconds = prompt("4] Введите секунды: [0 - 59]");

function firth_answ(){
    if (23 >= firth_time_hour >= 0 && 59 >= firth_time_minute >= 0 && 59 >= firth_time_seconds >= 0 )
        {return `Все корректно !
        Вы указали время: ${firth_time_hour}:${firth_time_minute}:${firth_time_seconds}`}
    else {return `Ошибка в указании времени.
        Вы написали время: ${firth_time_hour}:${firth_time_minute}:${firth_time_seconds}`}
}

document.getElementById("h1_4").textContent = `4] ${firth_answ()}`;

// 5

let five_x = prompt("Введите координаты 'x'");
let five_y = prompt("Введите координаты 'y'");

function five_answ(){
    if (five_x > 0 && five_y > 0) {return `1 четверть`}
    if (five_x < 0 && five_y > 0) {return `2 четверть`}
    if (five_x > 0 && five_y < 0) {return `4 четверть`}
    if (five_x < 0 && five_y < 0) {return `3 четверть`}
    else {return `Координаты указывают на центр между четвертями`}
}

document.getElementById("h1_5").textContent = `5] ${five_answ()}. Координаты: X(${five_x}), Y(${five_y})`;


// switch
// 1

let switch_first = prompt("(Switch 1) Введите номер месяца (1-12)");

function switch_first_answ(){
    switch(switch_first){
        case '1': return `Январь`;
        case '2': return `февраль`;
        case '3': return `март`;
        case '4': return `апрель`;
        case '5': return `май`;
        case '6': return `июнь`;
        case '7': return `июль`;
        case '8': return `август`;
        case '9': return `сентябрь`;
        case '10': return `октябрь`;
        case '11': return `ноябрь`;
        case '12': return `декабрь`;
        default: return `Такого месяца не существует`;
    }
}

document.getElementById("switch_1").textContent = `Switch.1] ${switch_first} == ${switch_first_answ()}`;

// 2


let switch_second_number_x = prompt("(Switch 2) Калькулятор: Введите первое число");
let switch_second_number_y = prompt("(Switch 2) Калькулятор: Введите второе число");
let switch_second_sign = prompt("(Switch 2) Калькулятор: Введите знак ('+' '-' '/' '*')");

function switch_second_answ(){
    switch(switch_second_sign){
        case '+': return `${switch_second_number_x} ${switch_second_sign} ${switch_second_number_y} = ${switch_second_number_x + switch_second_number_y}`;
        case '-': return `${switch_second_number_x} ${switch_second_sign} ${switch_second_number_y} = ${switch_second_number_x - switch_second_number_y}`;
        case '/': return `${switch_second_number_x} ${switch_second_sign} ${switch_second_number_y} = ${switch_second_number_x / switch_second_number_y}`;
        case '*': return `${switch_second_number_x} ${switch_second_sign} ${switch_second_number_y} = ${switch_second_number_x * switch_second_number_y}`;
        default: return `Неизвестный знак ${switch_second_sign}`;

    }
}

document.getElementById("switch_2").textContent = `Switch.2] ${switch_second_answ()}`;


// тернарные операторы
// 1

let tern_first_number_x = prompt("Tern.1] Введите первое число:");
let tern_first_number_y = prompt("Tern.1] Введите второе число:");

function tern_first_answ(){
    return tern_first_number_x > tern_first_number_y ?
    `${tern_first_number_x} больше ${tern_first_number_y}` :
    `${tern_first_number_x} меньше ${tern_first_number_y}`;
}

document.getElementById("tern_1").textContent = `Tern.1] ${tern_first_answ()}`;

// 2

let tern_second_number = prompt("Tern.2] Введите число на проверку кратности на 5");

function tern_second_answ(){
    return tern_second_number % 5 == 0 ? `${tern_second_number} кратно 5 !` : `${tern_second_number} не кратно 5 :(`
}

document.getElementById("tern_2").textContent = `Tern.2] ${tern_second_answ()}`;

// 3

let tern_third_planet = prompt("Введите название вашей планеты ('Земля', 'земля') или другая (если вы инопланетянен ахах)");

function tern_third_answ(){
    return tern_third_planet == "Земля" || tern_third_planet == "земля" ? `Привет,
    землянин!` : `Привет, инопланетянин!`;
}

document.getElementById("tern_3").textContent = tern_third_answ();