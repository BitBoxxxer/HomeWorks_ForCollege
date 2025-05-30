import 'package:flutter/material.dart';
import 'button.dart';

class calculateScreen extends StatefulWidget{
  const calculateScreen({super.key});

  @override
  State<calculateScreen> createState() => _calculateScreenState();

}

class _calculateScreenState extends State<calculateScreen>{
  String number1 ='';
  String number2 ='';
  String operator='';
  
  @override
  Widget build(BuildContext context) {
    final screenSize = MediaQuery.of(context).size; // нахождение размера экрана

    return Scaffold(
      body: SafeArea(
        child: Column(
          children: [
            Expanded(
              child: SingleChildScrollView(
                child: Container(
                  padding: const EdgeInsets.all(20),
                  child: Text(
                    '$number1$operator$number2'.isEmpty ? '0' :
                    '$number1$operator$number2',
                    style: const TextStyle(
                      fontSize: 40,
                      fontWeight: FontWeight.bold,
                    ),
                    textAlign: TextAlign.right,
                  ),
                )
              )
              ),
              // child: Container(
              // )
            Wrap(
                children: Buttn.buttonValues.map(
                  (value) => SizedBox(
                    width: value == Buttn.result ? screenSize.width / 2
                    : screenSize.width / 4,

                    height: screenSize.width / 4,
                    child: buildButton(value),
                  )
                ).toList(),
              )
          ],
        ),

      ),

    );
  }
  Widget buildButton(value){
    return Padding(
      padding: const EdgeInsets.all(8),
      child: Material(
        color: const Color.fromARGB(255, 97, 108, 74),
        shape: OutlineInputBorder (
           borderSide: const BorderSide(
             color: Color.fromARGB(255, 110, 102, 102)
           ),
          borderRadius: BorderRadius.circular(20),
        ),
        child: InkWell( // Inkwell - кликабельность калькулятора.
           onTap: () => 
             onBtnTap(value),
          child: Center(
            child: Text(
              value,
              style: const TextStyle(
                fontSize: 25,
                color: Color.fromARGB(255, 128, 231, 173),
                fontWeight: FontWeight.bold,
              )
            ),
          )
        )
      )
    );
  }

  void onBtnTap(String value){

    if (value == Buttn.result){
      calc();
      return;
    }
    if (value == Buttn.clr){
      clear();
      return;
    }
    if (value == Buttn.del){
      delete();
      return;
    }
    if (value == Buttn.per){
      convertPer();
      return;
    }

    appendValue(value);
  }

  void calc(){
    final double num1 = double.parse(number1);
    final double num2 = double.parse(number2);
    var result = 0.0;

    switch(operator)
      {
        case Buttn.add:
        result = num1 + num2;
          break;

        case Buttn.substract:
        result = num1-num2;
          break;

        case Buttn.divide:
        result = num1 / num2;
          break;

        case Buttn.multiply:
        result = num1 * num2;
          break;
      }

    setState(() {
      number1 = result.toStringAsPrecision(5); // 5 знаков после точко
    });
    operator = '';
    number2 = '';
  }

  void clear(){
    setState(() {
      number1 = '';
      number2 = '';
      operator = '';
    });
  }

  void delete(){
    if (number2.isNotEmpty){
      number2 = number2.substring(0, number2.length - 1);
    }
    else if (operator.isNotEmpty){
      operator = '';
    }
    else if(number1.isNotEmpty){
      number1 = number1.substring(0, number1.length - 1);
    }
    setState(() {});
  }
  
  void convertPer(){
    if(number1.isNotEmpty && operator.isNotEmpty && number2.isNotEmpty) {
      calc();
    }
    final number = double.parse(number1);
    setState(() {
      number1 = '${(number / 10)}';
      operator = '';
      number2 = '';
    });

  }

  void appendValue(String value){
    if (value != Buttn.dot && int.tryParse(value) == null)
    {
      if (operator.isNotEmpty && number2.isNotEmpty){
        calc();
      }
      operator = value;
    }
    else if(number1.isEmpty || operator.isEmpty){
       // number1.contains(Buttn.dot) Проверка содержимого number1
      if (value == Buttn.dot && number1.contains(Buttn.dot)) return;
      if (value == Buttn.dot && (number1.isEmpty || number1 == Buttn.dot)){
        value = '0,';
      }
      number1 += value;
    }
    else if(number2.isEmpty || operator.isNotEmpty){
       // number2.contains(Buttn.dot) Проверка содержимого number2
      if (value == Buttn.dot && number2.contains(Buttn.dot)) return;
      if (value == Buttn.dot && (number2.isEmpty || number2 == Buttn.dot)){
        value = '0,';
      }
      number2 += value;
    }
    setState(() {});
  }


}
