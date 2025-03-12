import 'package:flutter/material.dart';
import 'dart:async';

class MemoryGame extends StatefulWidget{
  const MemoryGame({super.key});
  @override
  State<MemoryGame> createState() => _Memory_gameState();
}

class _Memory_gameState extends State<MemoryGame>
{
  List<String> _cardValues = [];
  List<bool> _cardflipped = [];
  int _previousIndex = -1;
  bool _isChecking = false;
  int score = 0;
  late Timer _timer; int _timerLoss = 30;

  @override
  void initState(){
    super.initState();
    _startGame();
    _startTimer();
  }

  void _startGame() {
    List<String> cardValues= [
      'image/1.jpg',
      'image/2.jpg',
      'image/3.jpg',
      'image/4.jpg',
      'image/5.jpg',
      'image/Гастон.jpg',
    ];
    _cardValues = List.from(cardValues)..addAll(cardValues);
    // напомнить рассказать о двух точках.
    _cardValues.shuffle();
    _cardflipped = List.filled(_cardValues.length, false);
  }
  
  void _cardTapped(index){
    if (_isChecking || _cardflipped[index]) return;
    setState((){
      _cardflipped[index] = true;
    });

    if (_previousIndex == -1) {
      _previousIndex = index;
    } else {
      if (_cardValues[_previousIndex] == _cardValues[index]){
        _previousIndex = -1;
      } else {
        _isChecking = true;
        Future.delayed(Duration(seconds: 1), () {
          setState(() {
            _cardflipped[_previousIndex] = false;
            _cardflipped[index] = false;
            _previousIndex = -1; _isChecking = false;
          });
        });
      }
    }
  }

  void _startTimer(){
    _timer = Timer.periodic(const Duration(seconds: 1), (timer) {
      setState(() {
        if (_timerLoss > 0) {
          _timerLoss--;
        } else {
          _timer.cancel();
        }
      });
    });
  }

  @override
  Widget build(BuildContext context){
    return Scaffold( // создание экрана.
      appBar: AppBar(
        title: Text('Find Super-Idol.'),
      ),
      body: Column(children: [
        Padding(padding: 
        const EdgeInsets.all(10),
        child: Row(children: [
          Text('Время: $_timerLoss',)
        ],)
      ),
      Expanded(child:
      GridView.builder(
        gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
          crossAxisCount: 4,
          mainAxisSpacing: 3,
          crossAxisSpacing: 3,
        ),
        itemCount: _cardValues.length,
        itemBuilder: (context, index) {
          return GestureDetector(
            onTap:() => _cardTapped(index),
            child: Card(
              color: const Color.fromARGB(255, 33, 27, 27),
              child: Center(
                child: _cardflipped[index]
                  ? Image.asset(_cardValues[index])
                  : Container(),
              ),
            ),
          );
        },
      ),
      )
      ],)
    );
  }
}