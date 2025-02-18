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

  int answer = 0;
  
  @override
  Widget build(BuildContext context) {
    final screenSize = MediaQuery.of(context).size; // нахождение размера экрана

    return Scaffold(
      body: SafeArea(
        child: Column(
          children: [
            Text('This is Calculator from Kasey[17.02.25 - ]'),
          ],
          
        ),

      ),

    );
  }
}
