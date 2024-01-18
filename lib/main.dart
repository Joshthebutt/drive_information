import 'package:flutter/material.dart';
import 'dart:ffi';

final class DiskInfo extends Struct {
  @Int32()
  external int rawReadErrorRate;
}

// Define the function signature for the C function
typedef GetDiskInfoC = DiskInfo Function();

// Load the library

final dynamicLibrary = DynamicLibrary.open("path to the working.dll file"); // Replace with the actual DLL name


// Bind the C function to a Dart function
final getDiskInfo = dynamicLibrary
    .lookupFunction<GetDiskInfoC, DiskInfo Function()>('getDiskInfoWrapper');

void main() {

  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
 int rawReadErrorRate = -1;
  @override
  void initState() {
    super.initState();
    // Initialize the Dart FFI interface and fetch the data
    final diskInfo = getDiskInfo(); // Call the C function
    rawReadErrorRate = diskInfo.rawReadErrorRate;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Raw Read Error Rate"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              'Raw Read Error Rate:',
              style: TextStyle(fontSize: 24),
            ),
            Text(
              '$rawReadErrorRate',
              style: TextStyle(fontSize: 48, fontWeight: FontWeight.bold),
            ),

          ],
        ),
      ),
    );
  }
}