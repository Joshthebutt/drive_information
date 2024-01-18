import 'dart:ffi';

final DynamicLibrary yourDLL = DynamicLibrary.open("C:\\Users\\joshu\\Desktop\\driveadviser\\rawreaderror.dll");

class YourLibrary {
  // Define the Dart FFI function signature that matches your C++ function
  static int Function() getRawReadErrorRateWrapper = yourDLL
      .lookupFunction<Int32 Function(), int Function()>(
    'getRawReadErrorRateWrapper',
  );
}

