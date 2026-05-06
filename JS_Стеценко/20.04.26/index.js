// function words(text, maxWords = 30) {
//   const words = text.trim().split(/\s+/);
  
//   if (words.length <= maxWords) {
//     if (text.trim().endsWith('.')) {
//       return text + '..';
//     }
//     return text;
//   }

//   const firstPart = words.slice(0, maxWords).join(' ');
  
//   const lastChar = firstPart[firstPart.length - 1];
//   const suffix = (lastChar === '.') ? '..' : '...';
  
//   return firstPart + suffix;
// }

// const longText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
// console.log(words(longText));


// // 2

// function second_orig(str) {
//   const w = str.trim().split(/\s+/);
//   const i = Math.floor(w.length / 2);
  
//   if (w.length % 2 === 0) {
//     const ii = w.slice(0, i);
//     const ij = w.slice(i);
//     return [...ij, ...ii].join(' ');
//   } else {
//     const ii = w.slice(0, i);
//     const iw = w[i];
//     const ij = w.slice(i + 1);
//     return [...ij, iw, ...ii].join(' ');
//   }
// }

// function second(str) {
//   const i = str.trim().split(/\s+/);
//   if (i.length === 2) {
//     return i.reverse().join(' ');
//   }
//   return second_orig(str);
// }

// console.log(second('hello world'));
// console.log(second_orig('1 2 3 4'));


// // 3

// function third(str) {
//   return str.replaceAll('?', '');
// }
// console.log(third('Слон Тигр Шрек'));


// 4

function https_func(urlString) {
  const end = urlString.indexOf('://');
  const i = urlString.substring(0, end + 1);

  const j = urlString.substring(end + 3);

  const start = j.search(/[\/\?]/);
  let o, p;
  
  if (start === -1) {
    o = j;
    p = '';
  } else {
    o = j.substring(0, start);
    p = j.substring(start);
  }

  const inde = p.indexOf('?');
  let c, d;
  
  if (inde === -1) {
    c = p;
    d = '';
  } else {
    c = p.substring(0, inde);
    d = p.substring(inde);
  }

  return { i, o, c, d };
}

const https = 'https://dns-shop.ru/catalog/personal/?price=20000&brand=asus';
const a = https_func(https);

console.log(`Протокол: "${a.i}"\n Домен: "${a.o}"\n url: "${a.c}"\n query: "${a.d}"`);