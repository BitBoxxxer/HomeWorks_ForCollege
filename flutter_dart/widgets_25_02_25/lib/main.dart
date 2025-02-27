import 'package:flutter/material.dart';
import "image.dart";

void main() {
  runApp(const MainApp());
}

class MainApp extends StatelessWidget {
  const MainApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false, // убрать ленточку debug
      home: image_class(),

    );
  }
}
