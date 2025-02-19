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
      padding: const EdgeInsets.all(5),
      child: Material(
        color: const Color.fromARGB(255, 91, 72, 59),
        shape: OutlineInputBorder (
           borderSide: const BorderSide(
             color: Color.fromARGB(255, 110, 102, 102)
           ),
          borderRadius: BorderRadius.circular(10),
        ),
        child: InkWell( // Inkwell - кликабельность калькулятора.
           onTap: () => (
             onBtnTap(value),
            
             ),
          child: Center(
            child: Text(
              value,
              style: const TextStyle(
                fontSize: 25,
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
  }

  void convertPer(){
    
  }

  void calc(){
    setState(() {
      operator = '+';
    });
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
  
}
