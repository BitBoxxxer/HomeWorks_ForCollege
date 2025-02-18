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
      title: "Calculator from Kasey",
      home: calculateScreen(),
      theme : ThemeData.dark(),
      );
  }
}
