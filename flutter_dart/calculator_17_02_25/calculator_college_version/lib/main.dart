import 'package:flutter/material.dart';
import 'screen.dart';

void main() {
  runApp(const MainApp());
}

class MainApp extends StatelessWidget {
  const MainApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: calculateScreen(),
      title: "Calculator from Kasey",
      theme : ThemeData.dark(),
      );
  }
}
