import 'package:flutter/material.dart';

class image_class extends StatefulWidget{
  const image_class({super.key});


  @override
  State<image_class> createState() => _image_classState();

}

class _image_classState extends State<image_class>
{
  @override
  Widget build(BuildContext context){

    return Scaffold(
      body: Container(
        decoration: BoxDecoration(
          color: const Color.fromARGB(255, 81, 35, 81),
          borderRadius: BorderRadius.only(
            topLeft: Radius.circular(100),
            bottomRight: Radius.circular(100)
          ),
          border: Border.all(
            color: const Color.fromARGB(255, 0, 0, 0),
            width: 5
            ),
            boxShadow: [
              BoxShadow(
                color: const Color.fromARGB(255, 42, 93, 34),
                spreadRadius: 5,
                //blurRadius: 50
              )
            ]
          /* image: DecorationImage(
            image: AssetImage('image/negr.jpg'),
            fit: BoxFit.cover,
          ) */
        ),
      )
      
       /* Image.asset(
          'image/negr.jpg',
          /* width: 200,
          height: 200, */
          fit: BoxFit.cover,
          ), */
        

    );
  }

}