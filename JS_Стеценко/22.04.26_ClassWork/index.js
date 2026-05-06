let input = prompt("Введите данные в формате: Имя: ...; Возраст: ...; Хобби: ... (поля в любом порядке)");
let err = "";

if (!input) {
    console.log("Ошибка: ввод не выполнен");
} else {
    let pairs = input.split(";");
    
    let Name = null;
    let Age = null;
    let Hobbi = null;
    
    for (let i = 0; i < pairs.length; i++) {
        let pair = pairs[i].trim();
        if (pair === "") continue;
        
        let ind = pair.indexOf(":");
        if (ind === -1) continue;
        
        let word = pair.slice(0, ind).trim().toLowerCase();
        let w = pair.slice(ind + 1).trim();
        
        if (word === "имя") {
            Name = w;
        } 
        else if (word === "возраст") {
            let ageNum = Number(w);
            if (isNaN(ageNum) || ageNum <= 0 || ageNum > 150) {
                err = "Ошибка: возраст должен быть положительным числом (1-150)";
                break;
            }
            Age = ageNum;
        } 
        else if (word === "хобби") {
            let arr = w.split(",");
            for (let j = 0; j < arr.length; j++) {
                arr[j] = arr[j].trim();
            }
            Hobbi = arr;
        }
    }
    
    let hasError = false;
    if (Name === null) {
        err += " Ошибка: нету имя.";
        hasError = true;
    }
    if (Age === null) {
        err += " Ошибка: нету возраст.";
        hasError = true;
    }
    if (Hobbi === null) {
        err += " Ошибка: нету хобби.";
        hasError = true;
    }
    
    if (!hasError) {
        document.getElementById("name").textContent = `Имя пользователя: ${Name}`
        document.getElementById("age").textContent = `возраст: ${Age}`
        document.getElementById("hobby").textContent = `хобби: ${Hobbi}`
    } else {
        document.getElementById("err").textContent =
        `[У вас есть ошибка, конкретнее вот сообщение: ${err}]`;
    }
}